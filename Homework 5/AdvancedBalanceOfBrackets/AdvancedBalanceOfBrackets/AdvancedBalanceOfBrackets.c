#include <stdio.h>
#include <stdbool.h>

#include "..\..\Stack\Stack\Stack.h"
#include "..\..\Stack\Stack\TestsForStack.h"

bool isCorrectSymbol(const char symbolFromBracketsSequence)
{
    return symbolFromBracketsSequence == '{' || symbolFromBracketsSequence == '}' ||
        symbolFromBracketsSequence == '(' ||
        symbolFromBracketsSequence == ')' || symbolFromBracketsSequence == '[' ||
        symbolFromBracketsSequence == ']' || symbolFromBracketsSequence == ' ';
}

int returnIndexFromArray(char array[], char symbol, int lengthOfArray)
{
    for (int i = 0; i < lengthOfArray; ++i)
    {
        if (array[i] == symbol)
        {
            return i;
        }
    }
    return -1;
}

bool checkBracketsBalance(const char bracketsSequence[], bool* checkOfCorrectWork)
{
    StackElement* head = NULL;
    bool checkOfCorrectWorkOfStackFunctions = true;
    int i = 0;
    char arrayOfBrackets[6] = { '[', ']', '(', ')', '{', '}' };
    while (bracketsSequence[i] != '\0')
    {
        if (!isCorrectSymbol(bracketsSequence[i]))
        {
            deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
            return false;
        }
        if (bracketsSequence[i] == ' ')
        {
            ++i;
            continue;
        }
        int indexOfBracket = returnIndexFromArray(arrayOfBrackets, bracketsSequence[i], 6);
        if (indexOfBracket % 2 != 0)
        {
            if (isEmpty(head) || top(&head, &checkOfCorrectWorkOfStackFunctions)
                != arrayOfBrackets[indexOfBracket - 1])
            {
                deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
                return false;
            }
            else 
            {
                pop(&head, &checkOfCorrectWorkOfStackFunctions);
            }
        }
        else
        {
            push(&head, bracketsSequence[i], &checkOfCorrectWorkOfStackFunctions);
        }
        ++i;
        if (!checkOfCorrectWorkOfStackFunctions)
        {
            *checkOfCorrectWork = false;
            deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
            return false;
        }
    }
    if (!checkOfCorrectWorkOfStackFunctions)
    {
        *checkOfCorrectWork = false;
        deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
        return false;
    }
    if (!isEmpty(head))
    {
        deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
        return false;
    }
    deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
    return true;
}

bool checkOfCheckOfBracketsBalance(char bracketsSequence[], bool expectedResult)
{
    bool checkOfCorrectWork = true;
    return checkBracketsBalance(bracketsSequence, &checkOfCorrectWork) == expectedResult
        && checkOfCorrectWork == true;
}

bool standartCorrectTest()
{
    char bracketsSequence[8] = { "({})" };
    return checkOfCheckOfBracketsBalance(bracketsSequence, true);
}

bool standartIncorrectTest()
{
    char bracketsSequence[6] = { "({)} "};
    return checkOfCheckOfBracketsBalance(bracketsSequence, false);
}

bool testWithIrrelevantSymbol()
{
    char bracketsSequence[6] = { "(){5} " };
    return checkOfCheckOfBracketsBalance(bracketsSequence, false);
}

bool correctTestWithSpaces()
{
    char bracketsSequence[10] = { "({[ ]}  )" };
    return checkOfCheckOfBracketsBalance(bracketsSequence, true);
}

bool incorrectTestWithOneTypeOfBrackets()
{
    char bracketsSequence[4] = { "(((" };
    return checkOfCheckOfBracketsBalance(bracketsSequence, false);
}

bool areBracketsBalanceTestsPassing()
{
    return standartCorrectTest() && standartIncorrectTest() &&
        testWithIrrelevantSymbol() && correctTestWithSpaces() &&
        incorrectTestWithOneTypeOfBrackets();
}

int main()
{
    StackElement* head = NULL;
    if (!areTestsPassing(&head))
    {
        printf("Stack's tests failed\n");
        return -1;
    }
    bool checkOfCorrectWork = true;
    deleteStack(&head, &checkOfCorrectWork);
    if (!checkOfCorrectWork)
    {
        printf("Error with stack's deletion");
        return -1;
    }
    if (!areBracketsBalanceTestsPassing())
    {
        printf("Tests of brackets sequence failed\n");
        return -1;
    }
    char bracketsSequence[30] = { '\0' };
    printf("Enter the brackets sequence: ");
    gets_s(bracketsSequence, 30);
    bool const result = checkBracketsBalance(bracketsSequence, &checkOfCorrectWork);
    if (!checkOfCorrectWork)
    {
        printf("Error from stack's functions");
        return -1;
    }
    result
        ? printf("\nThe brackets sequence is correct\n")
        : printf("\nThe brackets sequence is incorrect\n");
}
