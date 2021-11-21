#pragma warning(disable: 4996 6031 6066)

#include <stdio.h>

#include "../ParseTree/ParseTree.h"
#include "../ParseTree/ParseTreeTests.h"

int main()
{
    if (!areTestsPassed())
    {
        printf("Tests failed");
        return -1;
    }
    FILE* data = fopen("Data.txt", "r");
    char sequenceOfNumbersAndOperators[50] = { "\0" };
    fgets(sequenceOfNumbersAndOperators, 50, data);
    fclose(data);
    printf("The original arithmetic expression: %s", sequenceOfNumbersAndOperators);
    int indexOfSequence = 0;
    Node* parseTree = createNewNodeForParseTree(sequenceOfNumbersAndOperators,
        &indexOfSequence);
    int countOfNumbers = 0;
    printf("\nNew expression (from tree): ");
    int indexOfResultString = 0;
    int countOfBrackets = 0;
    prefixTraverse(parseTree, &countOfNumbers,
        sequenceOfNumbersAndOperators, &indexOfResultString, &countOfBrackets);
    addMissingBrackets(sequenceOfNumbersAndOperators, &indexOfResultString, &countOfBrackets);
    printf("%s", sequenceOfNumbersAndOperators);
    bool divisionByZero = false;
    int const result = calculateParseTree(parseTree, &divisionByZero);
    if (divisionByZero)
    {
        printf("\nIncorrect sequence\n");
        deleteParseTree(parseTree);
        return -1;
    }
    printf("\nExpression value: %d ", result);
    deleteParseTree(parseTree);
}
