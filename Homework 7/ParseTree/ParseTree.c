#pragma warning(disable: 4996 6031 6066)

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ParseTree.h"

typedef struct Node {
    int number;
    char symbol;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

typedef Node Tree;

Node* createNode()
{
    return calloc(1, sizeof(Node));
}

void deleteNode(Node* node)
{
    free(node);
}

void deleteParseTree(Tree* root)
{
    if (root == NULL)
    {
        return;
    }
    deleteParseTree(root->leftChild);
    deleteParseTree(root->rightChild);
    deleteNode(root);
}

bool isOperator(const char symbol)
{
    return symbol == '+' || symbol == '*' || symbol == '/' || symbol == '-';
}

bool isDigit(const char symbol)
{
    return symbol == '0' || symbol == '1' || symbol == '2' || symbol == '3' || symbol == '4'
        || symbol == '5' || symbol == '6' || symbol == '7' || symbol == '8' || symbol == '9';
}

bool isBracketOrSpace(const char symbol)
{
    return symbol == '(' || symbol == ')' || symbol == ' ';
}

int getNumberFromSequence(const char* stringOfNumbersAndOperators, unsigned int* index)
{
    char stringForNumber[30] = { '\0' };
    int indexOfStringForNumber = 0;
    while (isDigit(stringOfNumbersAndOperators[*index])
        || stringOfNumbersAndOperators[*index] == '-')
    {
        stringForNumber[indexOfStringForNumber] = stringOfNumbersAndOperators[*index];
        ++indexOfStringForNumber;
        ++(*index);
    }
    --(*index);
    return atoi(stringForNumber);
}

Node* createNewNodeForParseTree(const char* stringOfNumbersAndOperators, unsigned int* index)
{
    ++(*index);
    const unsigned int lengthOfString = (unsigned int)strlen(stringOfNumbersAndOperators);
    Node* newNode = createNode();
    while (*index < lengthOfString
        && isBracketOrSpace(stringOfNumbersAndOperators[*index]))
    {
        ++(*index);
    }
    if (isOperator(stringOfNumbersAndOperators[*index])
            && stringOfNumbersAndOperators[*index + 1] == ' ')
    {
        newNode->symbol = stringOfNumbersAndOperators[*index];
        newNode->leftChild = createNewNodeForParseTree(stringOfNumbersAndOperators,
            index);
        newNode->rightChild = createNewNodeForParseTree(stringOfNumbersAndOperators,
            index);
    }
    else if (isDigit(stringOfNumbersAndOperators[*index]) || stringOfNumbersAndOperators[*index] == '-')
    {
        newNode->number = getNumberFromSequence(stringOfNumbersAndOperators, index);
    }
    return newNode;
}

void symbolToAdd(char* string, unsigned int* indexForString, char symbolToAdding, bool spaceOption)
{
    string[*indexForString] = symbolToAdding;
    ++(*indexForString);
    if (spaceOption)
    {
        string[*indexForString] = ' ';
        ++(*indexForString);
    }
}

void prefixTraverse(const Tree* parseTree, char* stringForResult, unsigned int* indexForString)
{
    if (parseTree == NULL)
    {
        return;
    }
    if (parseTree->symbol == '\0')
    {
        char stringForNumber[30] = { "\0" };
        sprintf(stringForNumber, "%d", parseTree->number);
        int indexOfStringForNumber = 0;
        strcat(stringForResult, stringForNumber);
        ++(*indexForString);
        if (parseTree->number < 0)
        {
            ++(*indexForString);
        }
        symbolToAdd(stringForResult, indexForString, ' ', false);
    }
    else
    {
        symbolToAdd(stringForResult, indexForString, '(', true);
        symbolToAdd(stringForResult, indexForString, parseTree->symbol, true);
        prefixTraverse(parseTree->leftChild, stringForResult, indexForString);
        prefixTraverse(parseTree->rightChild, stringForResult, indexForString);
        symbolToAdd(stringForResult, indexForString, ')', true);
    }
}

int calculateParseTree(const Tree* parseTree, bool* divisionByZero)
{
    if (parseTree->leftChild == NULL && parseTree->rightChild == NULL)
    {
        return parseTree->number;
    }
    int firstElement = calculateParseTree(parseTree->leftChild, divisionByZero);
    int secondElement = calculateParseTree(parseTree->rightChild, divisionByZero);
    switch (parseTree->symbol)
    {
    case '+':
        return firstElement + secondElement;
    case '-':
        return firstElement - secondElement;
    case'*':
        return firstElement * secondElement;
    case '/':
        if (secondElement == 0)
        {
            *divisionByZero = true;
            break;
        }
        return firstElement / secondElement;
    }
    return -1;
}

Tree* buildParseTree(const char* string)
{
    int indexOfSequence = 0;
    Node* parseTree = createNewNodeForParseTree(string, &indexOfSequence);
    return parseTree;
}

void printParseTree(const Tree* parseTree)
{
    unsigned int indexOfResultString = 0;
    char resultSequenceOfNumbersAndOperators[50] = { '\0' };
    prefixTraverse(parseTree, resultSequenceOfNumbersAndOperators, &indexOfResultString);
    printf("%s", resultSequenceOfNumbersAndOperators);
}