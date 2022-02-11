#pragma warning(disable: 4996)

#include <stdio.h>
#include <string.h>

#include "ParseTreeTests.h"
#include "ParseTree.h"

bool checkOfCreatingParseTree()
{
    FILE* data = fopen("../../StandartTestData.txt", "r");
    if (data == NULL)
    {
        return -1;
    }
    char sequenceOfNumbersAndOperators[50] = { '\0' };
    fgets(sequenceOfNumbersAndOperators, 50, data);
    fclose(data);
    Tree* parseTree = buildParseTree(sequenceOfNumbersAndOperators);
    int indexOfSequence = 0;
    char stringForResult[50] = { '\0' };
    prefixTraverse(parseTree, stringForResult, &indexOfSequence);
    const char* expectedResult = "( * ( + 3 5 ) ( - 8 ( * 3 5 ) ) ) ";
    deleteParseTree(parseTree);
    return strcmp(expectedResult, stringForResult) == 0;
}

bool checkOfCalculatingParseTree()
{
    FILE* data = fopen("../../StandartTestData.txt", "r");
    if (data == NULL)
    {
        return -1;
    }
    char sequenceOfNumbersAndOperators[50] = { '\0' };
    fgets(sequenceOfNumbersAndOperators, 50, data);
    fclose(data);
    Tree* parseTree = buildParseTree(sequenceOfNumbersAndOperators);
    int expectedResult = 56;
    bool divisionByZero = false;
    if (calculateParseTree(parseTree, &divisionByZero) != -56 || divisionByZero)
    {
        deleteParseTree(parseTree);
        return false;
    }
    deleteParseTree(parseTree);
    data = fopen("../../TestDataWithDivisionByZero.txt", "r");
    if (data == NULL)
    {
        return -1;
    }
    fgets(sequenceOfNumbersAndOperators, 50, data);
    fclose(data);
    parseTree = buildParseTree(sequenceOfNumbersAndOperators);
    expectedResult = calculateParseTree(parseTree, &divisionByZero);
    deleteParseTree(parseTree);
    return divisionByZero;
}

bool areTestsPassed()
{
    return checkOfCalculatingParseTree() && checkOfCreatingParseTree();
}

