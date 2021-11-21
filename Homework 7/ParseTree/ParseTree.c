#pragma warning(disable: 4996 6031 6066)

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../ParseTree/ParseTree.h"

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
    if (root->leftChild != NULL)
    {
        deleteParseTree(root->leftChild);
    }
    if (root->rightChild != NULL)
    {
        deleteParseTree(root->rightChild);
    }
    deleteNode(root);
}

bool isOperatorInString(char symbol)
{
    return symbol == '+' || symbol == '*' || symbol == '/';
}

bool isNumberInString(char symbol)
{
    return symbol != '(' && symbol != ')' && symbol != ' ';
}

Node* createNewNodeForParseTree(char* stringOfNumbersAndOperators, int* index)
{
    ++(*index);
    const int lengthOfString = (int)strlen(stringOfNumbersAndOperators);
    Node* newNode = createNode();
    while (*index < lengthOfString
        && !isNumberInString(stringOfNumbersAndOperators[*index]))
    {
        ++(*index);
    }
    if (isOperatorInString(stringOfNumbersAndOperators[*index])
        || (stringOfNumbersAndOperators[*index] == '-'
            && stringOfNumbersAndOperators[*index + 1] == ' '))
    {
        newNode->symbol = stringOfNumbersAndOperators[*index];
        newNode->leftChild = createNewNodeForParseTree(stringOfNumbersAndOperators,
            index);
        newNode->rightChild = createNewNodeForParseTree(stringOfNumbersAndOperators,
            index);
    }
    else if (isNumberInString(stringOfNumbersAndOperators[*index]))
    {
        char stringForNumber[30] = { '\0' };
        int indexOfStringForNumber = 0;
        while (isNumberInString(stringOfNumbersAndOperators[*index])
            && !isOperatorInString(stringOfNumbersAndOperators[*index]))
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

void addToString(char* string, int* indexForString, char symbolToAdding, bool spaceOption)
{
    string[*indexForString] = symbolToAdding;
    ++(* indexForString);
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
        addToString(stringForResult, indexForString, ')', true);
    }
}

void prefixTraverse(Node* parseTree, int* countOfNumbers,
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
            addToString(stringForResult, indexForString,
                stringForNumber[indexOfStringForNumber], false);
            ++indexOfStringForNumber;
        }
        addToString(stringForResult, indexForString, ' ', false);
        ++(*countOfNumbers);
        if (*countOfNumbers >= 2)
        {
            addToString(stringForResult, indexForString, ')', true);
            --(*countOfBrackets);
            *countOfNumbers = 0;
        }
    }
    else
    {
        addToString(stringForResult, indexForString, '(', true);
        ++(*countOfBrackets);
        addToString(stringForResult, indexForString, parseTree->symbol, true);
        *countOfNumbers = 0;
    }
    prefixTraverse(parseTree->leftChild, countOfNumbers,
        stringForResult, indexForString, countOfBrackets);
    prefixTraverse(parseTree->rightChild, countOfNumbers,
        stringForResult, indexForString, countOfBrackets);
}

int calculateParseTree(Node* parseTree, bool* divisionByZero)
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