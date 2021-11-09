#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "..\..\Stack\Stack\TestsForStack.h"
#include "..\..\Stack\Stack\Stack.h"

int calculateInPostfixForm(char commandSequence[],
    bool* ñheckOfDivisionByZero, bool* checkOfCorrectWork)
{
    StackElement* head = NULL;
    if (!areTestsPassing(&head))
    {
        *checkOfCorrectWork = false;
        return -1;
    }
    bool checkOfCorrectWorkOfStackFunctions = true;
    int i = 0;
    while (commandSequence[i] != '\0')
    {
        int firstElement = 0;
        int secondElement = 0;
        int number = 0;
        if (commandSequence[i] == '*' || commandSequence[i] == '/'
            || commandSequence[i] == '+' || commandSequence[i] == '-')
        {
            firstElement = pop(&head, &checkOfCorrectWorkOfStackFunctions);
            secondElement = pop(&head, &checkOfCorrectWorkOfStackFunctions);
            if (!checkOfCorrectWorkOfStackFunctions)
            {
                *checkOfCorrectWork = false;
                return  -1;
            }
        }
        switch (commandSequence[i])
        {
        case ' ':
            break;
        case '\n':
            break;
        default:
            switch (commandSequence[i])
            {
            case '*':
                number = firstElement * secondElement;
                break;
            case '/':
                if (firstElement == 0)
                {
                    *ñheckOfDivisionByZero = true;
                    return -1;
                }
                number = secondElement / firstElement;
                break;
            case '-':
                number = secondElement - firstElement;
                break;
            case '+':
                number = firstElement + secondElement;
                break;
            default:
                number = commandSequence[i] - '0';
                break;
            }
            push(&head, number, &checkOfCorrectWorkOfStackFunctions);
            if (!checkOfCorrectWorkOfStackFunctions)
            {
                *checkOfCorrectWork = false;
                return -1;
            }
            break;
        }
        ++i;
    }
    int const result = pop(&head, &checkOfCorrectWorkOfStackFunctions);
    deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
    if (!checkOfCorrectWorkOfStackFunctions)
    {
        *checkOfCorrectWork = false;
        return -1;
    }
    return result;
}

bool checkOfCalculation(char commandSequence[], int expectedResult)
{
    bool checkOfDivisionByZero = false;
    bool checkOfCorrectWork = true;
    return calculateInPostfixForm(commandSequence, &checkOfDivisionByZero, &checkOfCorrectWork)
        == expectedResult;
}

bool standartTest()
{
    char commandSequence[19] = { "9 5 * 3 / 9 1 + -" };
    return checkOfCalculation(commandSequence, 5);
}

bool divisionByZeroTest()
{
    char commandSequence[19] = { "9 5 * 0 / 9 1 + -" };
    return checkOfCalculation(commandSequence, -1);
}

bool zeroResultTest()
{
    char commandSequence[15] = { "3 5 - 8 + 0 *" };
    return checkOfCalculation(commandSequence, 0);
}

bool testOfIncorrectSequence()
{
    char commandSequence[15] = { "3 * 5 - 8 + 0 *" };
    return checkOfCalculation(commandSequence, -1);
}

int main()
{
    if (!standartTest() || !divisionByZeroTest() || !zeroResultTest() || !testOfIncorrectSequence())
    {
        printf("Tests failed");
        return -1;
    }
    char commandSequence[30] = { '\0' };
    printf("Enter the sequence of digits and operations (in postfix form): ");
    gets_s(commandSequence, 30);
    bool isDivisionByZero = false;
    bool checkOfCorrectWork = true;
    int const resultOfCalculation = calculateInPostfixForm(commandSequence,
        &isDivisionByZero, &checkOfCorrectWork);
    if (isDivisionByZero)
    {
        printf("\nIncorrect form: division by zero.\n");
        return -1;
    }
    if (!checkOfCorrectWork)
    {
        printf("\nIncorrect sequence.\n");
        return -1;
    }
    printf("\nThe calculation result: %d\n", resultOfCalculation);
}
