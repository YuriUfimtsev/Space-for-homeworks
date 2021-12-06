#pragma warning(disable: 4996 6031 6066)

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../ParseTree/ParseTree.h"

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

void deleteParseTree(Node* root)
{
    if (root == NULL)
    {
        return;
    }
    deleteParseTree(root->leftChild);
    deleteParseTree(root->rightChild);
    deleteNode(root);
}

bool isOperator(const char symbol) //
{
    return symbol == '+' || symbol == '*' || symbol == '/' || symbol == '-';
}

bool isDigit(const char symbol)
{
    return symbol != '(' && symbol != ')' && symbol != ' ';
}

Node* createNewNodeForParseTree(const char* stringOfNumbersAndOperators, int* index)
{
    ++(*index);
    const int lengthOfString = (int)strlen(stringOfNumbersAndOperators);
    Node* newNode = createNode();
    while (*index < lengthOfString
        && !isDigit(stringOfNumbersAndOperators[*index]))
    {
        ++(*index);
    }
    if (isOperator(stringOfNumbersAndOperators[*index])
        || (stringOfNumbersAndOperators[*index] == '-'
            && stringOfNumbersAndOperators[*index + 1] == ' '))
    {
        newNode->symbol = stringOfNumbersAndOperators[*index];
        newNode->leftChild = createNewNodeForParseTree(stringOfNumbersAndOperators,
            index);
        newNode->rightChild = createNewNodeForParseTree(stringOfNumbersAndOperators,
            index);
    }
    else if (isDigit(stringOfNumbersAndOperators[*index]))
    {
        char stringForNumber[30] = { '\0' };
        int indexOfStringForNumber = 0;
        while (isDigit(stringOfNumbersAndOperators[*index])
            && !isOperator(stringOfNumbersAndOperators[*index]))
        {
            stringForNumber[indexOfStringForNumber] = stringOfNumbersAndOperators[*index];
            ++indexOfStringForNumber;
            ++(*index);
        }
        --(*index);
        int number = atoi(stringForNumber);
        newNode->number = number;
    }
    return newNode;
}

void symbolToAdd(char* string, int* indexForString, char symbolToAdding, bool spaceOption)
{
    string[*indexForString] = symbolToAdding;
    ++(*indexForString);
    if (spaceOption)
    {
        string[*indexForString] = ' ';
        ++(*indexForString);
    }
}

void addMissingBrackets(char* stringForResult, int* indexForString, int* countOfBrackets)
{
    for (int i = 0; i < *countOfBrackets; ++i)
    {
        symbolToAdd(stringForResult, indexForString, ')', true);
    }
}

void prefixTraverse(const Tree* parseTree, int* countOfNumbers,
    char* stringForResult, int* indexForString, int* countOfBrackets)
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
        while (stringForNumber[indexOfStringForNumber] != '\0')
        {
            symbolToAdd(stringForResult, indexForString,
                stringForNumber[indexOfStringForNumber], false);
            ++indexOfStringForNumber;
        }
        symbolToAdd(stringForResult, indexForString, ' ', false);
        ++(*countOfNumbers);
        if (*countOfNumbers >= 2)
        {
            symbolToAdd(stringForResult, indexForString, ')', true);
            --(*countOfBrackets);
            *countOfNumbers = 0;
        }
    }
    else
    {
        symbolToAdd(stringForResult, indexForString, '(', true);
        ++(*countOfBrackets);
        symbolToAdd(stringForResult, indexForString, parseTree->symbol, true);
        *countOfNumbers = 0;
    }
    prefixTraverse(parseTree->leftChild, countOfNumbers,
        stringForResult, indexForString, countOfBrackets);
    prefixTraverse(parseTree->rightChild, countOfNumbers,
        stringForResult, indexForString, countOfBrackets);
}

int calculateParseTree(const Tree* parseTree, bool* divisionByZero)
{
    int firstElement = 0;
    int secondElement = 0;
    if (parseTree->leftChild == NULL && parseTree->rightChild == NULL)
    {
        return parseTree->number;
    }
    firstElement = calculateParseTree(parseTree->leftChild, divisionByZero);
    secondElement = calculateParseTree(parseTree->rightChild, divisionByZero);
    switch (parseTree->symbol)
    {
    case '+':
        return firstElement + secondElement;
        break;
    case '-':
        return firstElement - secondElement;
        break;
    case'*':
        return firstElement * secondElement;
        break;
    case '/':
        if (secondElement == 0)
        {
            *divisionByZero = true;
            break;
        }
        return firstElement / secondElement;
        break;
    }
    if (*divisionByZero)
    {
        return -1;
    }
}

Tree* buildTree(const char* string)
{
    int indexOfSequence = 0;
    Node* parseTree = createNewNodeForParseTree(string, &indexOfSequence);
    return parseTree;
}

void printParseTree(const Tree* parseTree)
{
    int indexOfResultString = 0;
    int countOfNumbers = 0;
    int countOfBrackets = 0;
    char resultSequenceOfNumbersAndOperators[50] = { '\0' };
    prefixTraverse(parseTree, &countOfNumbers,
        resultSequenceOfNumbersAndOperators, &indexOfResultString, &countOfBrackets);
    addMissingBrackets(resultSequenceOfNumbersAndOperators, &indexOfResultString, &countOfBrackets);
    printf("%s", resultSequenceOfNumbersAndOperators);
}