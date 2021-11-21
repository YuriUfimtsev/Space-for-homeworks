#pragma warning(disable: 4996 6031 6066)

#include <stdio.h>

#include "../ParseTree/ParseTree.h"

int main()
{
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
    prefixTraverse(parseTree, &countOfNumbers);
    printf(")");
    bool divisionByZero = false;
    int const result = calculateParseTree(parseTree, &divisionByZero);
    if (divisionByZero)
    {
        printf("\nIncorrect sequence\n");
        deleteTree(parseTree);
        return -1;
    }
    printf("\nExpression value: %d ", result);
    deleteTree(parseTree);
}
