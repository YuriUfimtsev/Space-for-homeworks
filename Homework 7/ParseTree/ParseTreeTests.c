#pragma warning(disable: 4996)

#include <stdio.h>
#include <string.h>

#include "../ParseTree/ParseTreeTests.h"

bool checkOfCreatingParseTree()
{
    FILE* data = fopen("StandartTestData.txt", "r");
    char sequenceOfNumbersAndOperators[50] = { "\0" };
    fgets(sequenceOfNumbersAndOperators, 50, data);
    fclose(data);
    int indexOfSequence = 0;
    Node* parseTree = createNewNodeForParseTree(sequenceOfNumbersAndOperators,
        &indexOfSequence);
    int countOfNumbers = 0;
    indexOfSequence = 0;
    int countOfBrackets = 0;
    prefixTraverse(parseTree, &countOfNumbers,
        sequenceOfNumbersAndOperators, &indexOfSequence, &countOfBrackets);
    addMissingBrackets(sequenceOfNumbersAndOperators, &indexOfSequence, &countOfBrackets);
    char* expectedResult = "( * ( + 3 5 ) ( - 8 ( * 3 5 ) ) ) ";
    if (strcmp(expectedResult, sequenceOfNumbersAndOperators) != 0)
    {
        deleteParseTree(parseTree);
        return false;
    }
    deleteParseTree(parseTree);
    return true;
}

bool checkOfCalculatingParseTree()
{
    FILE* data = fopen("StandartTestData.txt", "r");
    char sequenceOfNumbersAndOperators[50] = { "\0" };
    fgets(sequenceOfNumbersAndOperators, 50, data);
    fclose(data);
    int indexOfSequence = 0;
    Node* parseTree = createNewNodeForParseTree(sequenceOfNumbersAndOperators,
        &indexOfSequence);
    int expectedResult = 56;
    bool divisionByZero = false;
    if (calculateParseTree(parseTree, &divisionByZero) != -56 || divisionByZero)
    {
        deleteParseTree(parseTree);
        return false;
    }
    deleteParseTree(parseTree);
    data = fopen("TestDataWithDivisionByZero.txt", "r");
    fgets(sequenceOfNumbersAndOperators, 50, data);
    fclose(data);
    indexOfSequence = 0;
    parseTree = createNewNodeForParseTree(sequenceOfNumbersAndOperators,
        &indexOfSequence);
    expectedResult = calculateParseTree(parseTree, &divisionByZero);
    if (!divisionByZero)
    {
        deleteParseTree(parseTree);
        return false;
    }
    deleteParseTree(parseTree);
    return true;
}

bool areTestsPassed()
{
    return checkOfCalculatingParseTree() && checkOfCreatingParseTree();
}

