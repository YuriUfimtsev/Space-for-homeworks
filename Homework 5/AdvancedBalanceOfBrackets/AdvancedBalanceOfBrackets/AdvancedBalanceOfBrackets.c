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

bool checkOfBracketBalance(const char bracketsSequence[], bool* checkOfCorrectWork)
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
            return false;
        }
        if (bracketsSequence[i] == ' ')
        {
            ++i;
            continue;
        }
        else if (bracketsSequence[i] == ')')
        {
            if (isEmpty(head))
            {
                return false;
            }
            if (top(&head, &checkOfCorrectWorkOfStackFunctions) == '(')
            {
                pop(&head, &checkOfCorrectWorkOfStackFunctions);
            }
            else
            {
                return false;
            }
        }
        else if (bracketsSequence[i] == ']')
        {
            if (isEmpty(head))
            {
                return false;
            }
            if (top(&head, &checkOfCorrectWorkOfStackFunctions) == '[')
            {
                pop(&head, &checkOfCorrectWorkOfStackFunctions);
            }
            else
            {
                return false;
            }
        }
        else if (bracketsSequence[i] == '}')
        {
            if (isEmpty(head))
            {
                return false;
            }
            if (top(&head, &checkOfCorrectWorkOfStackFunctions) == '{')
            {
                pop(&head, &checkOfCorrectWorkOfStackFunctions);
            }
            else
            {
                return false;
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
            return false;
        }
    }
    if (!checkOfCorrectWorkOfStackFunctions)
    {
        *checkOfCorrectWork = false;
        return false;
    }
    if (!isEmpty(head))
    {
        deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
        return false;
    }
    return true;
}

bool checkOfCheckOfBracketBalance(char bracketsSequence[], bool expectedResult)
{
    bool checkOfCorrectWork = true;
    return checkOfBracketBalance(bracketsSequence, &checkOfCorrectWork) == expectedResult;
}

bool standartCorrectTest()
{
    char bracketsSequence[8] = { "({})" };
    return checkOfCheckOfBracketBalance(bracketsSequence, true);
}

bool standartIncorrectTest()
{
    char bracketsSequence[6] = { "({)} "};
    return checkOfCheckOfBracketBalance(bracketsSequence, false);
}

bool testWithIrrelevantSymbol()
{
    char bracketsSequence[6] = { "(){5} " };
    return checkOfCheckOfBracketBalance(bracketsSequence, false);
}

bool correctTestWithSpaces()
{
    char bracketsSequence[10] = { "({[ ]}  )" };
    return checkOfCheckOfBracketBalance(bracketsSequence, true);
}

bool incorrectTestWithOneTypeOfBrackets()
{
    char bracketsSequence[4] = { "(((" };
    return checkOfCheckOfBracketBalance(bracketsSequence, false);
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
    bool const result = checkOfBracketBalance(bracketsSequence, &checkOfCorrectWork);
    if (!checkOfCorrectWork)
    {
        printf("Error from stack's functions");
        return -1;
    }
    result ? printf("\nThe bracket sequence is correct\n")
        : printf("\nThe bracket sequence is incorrect\n");
}
