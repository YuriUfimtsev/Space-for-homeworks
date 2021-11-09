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

bool checkOfBracketsBalance(const char bracketsSequence[], bool* checkOfCorrectWork)
{
    StackElement* head = NULL;
    if (!areTestsPassing(&head))
    {
        *checkOfCorrectWork = false;
        return false;
    }
    bool checkOfCorrectWorkOfStackFunctions = true;
    int i = 0;
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
        else if (bracketsSequence[i] == ')')
        {
            if (isEmpty(head) || top(&head, &checkOfCorrectWorkOfStackFunctions) != '(')
            {
                deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
                return false;
            }
            else 
            {
                pop(&head, &checkOfCorrectWorkOfStackFunctions);
            }
        }
        else if (bracketsSequence[i] == ']')
        {
            if (isEmpty(head) || top(&head, &checkOfCorrectWorkOfStackFunctions) != '[')
            {
                deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
                return false;
            }
            else
            {
                pop(&head, &checkOfCorrectWorkOfStackFunctions);
            }
        }
        else if (bracketsSequence[i] == '}')
        {
            if (isEmpty(head) || top(&head, &checkOfCorrectWorkOfStackFunctions) != '{')
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
    return checkOfBracketsBalance(bracketsSequence, &checkOfCorrectWork) == expectedResult;
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
    if (!areBracketsBalanceTestsPassing())
    {
        printf("Tests of brackets sequence failed\n");
        return -1;
    }
    char bracketsSequence[30] = { '\0' };
    printf("Enter the bracket sequence: ");
    gets_s(bracketsSequence, 30);
    bool checkOfCorrectWork = true;
    bool const result = checkOfBracketsBalance(bracketsSequence, &checkOfCorrectWork);
    if (!checkOfCorrectWork)
    {
        printf("Error from stack's functions");
        return -1;
    }
    result
        ? printf("\nThe bracket sequence is correct\n")
        : printf("\nThe bracket sequence is incorrect\n");
}
