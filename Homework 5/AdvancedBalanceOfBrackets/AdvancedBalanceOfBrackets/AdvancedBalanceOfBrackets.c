#include <stdio.h>
#include <stdbool.h>

#include "C:\Users\Home\source\repos\Space-for-homeworks\Homework 5\Stack\Stack\Stack.h"
#include "C:\Users\Home\source\repos\Space-for-homeworks\Homework 5\Stack\Stack\TestsForStack.h"

bool checkOfBracketBalance(char bracketsSequence[], StackElement** head)
{
    int i = 0;
    while (bracketsSequence[i] != '\0')
    {
        if (!(bracketsSequence[i] == '{' || bracketsSequence[i] == '}' || bracketsSequence[i] == '(' ||
            bracketsSequence[i] == ')' || bracketsSequence[i] == '[' || bracketsSequence[i] == ']'
            || bracketsSequence[i] == ' '))
        {
            return false;
        }
        if (bracketsSequence[i] != ' ')
        {
            if (bracketsSequence[i] == ')' || bracketsSequence[i] == '}' || bracketsSequence[i] == ']')
            {
                if (bracketsSequence[i] == ')')
                {
                    if (top(head) == '(')
                    {
                        pop(head);
                    }
                    else
                    {
                        return false;
                    }
                }
                if (bracketsSequence[i] == ']')
                {
                    if (top(head) == '[')
                    {
                        pop(head);
                    }
                    else
                    {
                        return false;
                    }
                }
                if (bracketsSequence[i] == '}')
                {
                    if (top(head) == '{')
                    {
                        pop(head);
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            else
            {
                push(head, bracketsSequence[i]);
            }
        }
        ++i;
    }
    return true;
}

bool checkOfCheckOfBracketBalance(char bracketsSequence[], bool expectedResult)
{
    StackElement* headForTests = NULL;
    return checkOfBracketBalance(bracketsSequence, &headForTests) == expectedResult;
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

int main()
{
    StackElement* head = NULL;
    if (!areTestsPassing(&head))
    {
        printf("Stack's tests failed");
        return -1;
    }
    if (!standartCorrectTest() || !standartIncorrectTest() || !testWithIrrelevantSymbol() || !correctTestWithSpaces())
    {
        printf("Tests of bracker sequence failed");
        return -1;
    }
    char bracketsSequence[30] = { '\0' };
    printf("Enter the bracket sequence: ");
    gets_s(bracketsSequence, 30);
    checkOfBracketBalance(bracketsSequence, &head) ? printf("\nThe bracket sequence is correct\n") 
    : printf("\nThe bracket sequence is incorrect\n");
}
