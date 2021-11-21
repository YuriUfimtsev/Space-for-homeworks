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

void deleteTree(Node* root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->leftChild != NULL)
    {
        deleteTree(root->leftChild);
    }
    if (root->rightChild != NULL)
    {
        deleteTree(root->rightChild);
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
        newNode->key = number;
    }
    return newNode;
}

void prefixTraverse(Node* tree, int* countOfNumbers)
{
    if (tree == NULL)
    {
        return;
    }
    if (tree->symbol == '\0')
    {
        printf("%d ", tree->key);
        ++(*countOfNumbers);
        if (*countOfNumbers == 2)
        {
            printf(") ");
            *countOfNumbers = 0;
        }
    }
    else
    {
        printf("( ");
        printf("%c ", tree->symbol);
        *countOfNumbers = 0;
    }
    prefixTraverse(tree->leftChild, countOfNumbers);
    prefixTraverse(tree->rightChild, countOfNumbers);
}

int calculateParseTree(Node* tree, bool* divisionByZero)
{
    int firstElement = 0;
    int secondElement = 0;
    if (tree->leftChild == NULL && tree->rightChild == NULL)
    {
        return tree->key;
    }
    firstElement = calculateParseTree(tree->leftChild, divisionByZero);
    secondElement = calculateParseTree(tree->rightChild, divisionByZero);
    switch (tree->symbol)
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