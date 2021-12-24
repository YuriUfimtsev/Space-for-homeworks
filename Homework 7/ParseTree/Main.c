#pragma warning(disable: 4996 6031 6066)

#include <stdio.h>

#include "ParseTree.h"
#include "ParseTreeTests.h"

int main()
{
    if (!areTestsPassed())
    {
        printf("Tests failed");
        return -1;
    }
    FILE* data = fopen("Data.txt", "r");
    char sequenceOfNumbersAndOperators[50] = { '\0' };
    fgets(sequenceOfNumbersAndOperators, 50, data);
    fclose(data);
    printf("The original arithmetic expression: %s", sequenceOfNumbersAndOperators);
    Tree* parseTree = buildParseTree(sequenceOfNumbersAndOperators);
    printf("\nNew expression (from tree): ");
    printParseTree(parseTree);
    bool divisionByZero = false;
    int const result = calculateParseTree(parseTree, &divisionByZero);
    deleteParseTree(parseTree);
    if (divisionByZero)
    {
        printf("\nIncorrect sequence\n");
        return -1;
    }
    printf("\nExpression value: %d \n", result);
}
