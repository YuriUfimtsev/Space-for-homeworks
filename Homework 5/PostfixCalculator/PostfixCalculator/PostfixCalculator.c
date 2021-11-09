#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "..\..\Stack\Stack\TestsForStack.h"
#include "..\..\Stack\Stack\Stack.h"

int calculateInPostfixForm(char commandSequence[],
    bool* pointerToCheckOfDivisionByZero, bool* checkOfCorrectWork)
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
        switch (commandSequence[i])
        {
        case ' ':
            break;
        case '\n':
            break;
        case '*':
            firstElement = pop(&head, &checkOfCorrectWorkOfStackFunctions);
            secondElement = pop(&head, &checkOfCorrectWorkOfStackFunctions);
            firstElement *= secondElement;
            push(&head, firstElement, &checkOfCorrectWorkOfStackFunctions);
            break;
        case '/':
            firstElement = pop(&head, &checkOfCorrectWorkOfStackFunctions);
            secondElement = pop(&head, &checkOfCorrectWorkOfStackFunctions);
            if (firstElement == 0)
            {
                *pointerToCheckOfDivisionByZero = true;
                return -1;
            }
            firstElement = secondElement / firstElement;
            push(&head, firstElement, &checkOfCorrectWorkOfStackFunctions);
            break;
        case '-':
            firstElement = pop(&head, &checkOfCorrectWorkOfStackFunctions);
            secondElement = pop(&head, &checkOfCorrectWorkOfStackFunctions);
            firstElement = secondElement - firstElement;
            push(&head, firstElement, &checkOfCorrectWorkOfStackFunctions);
            break;
        case '+':
            firstElement = pop(&head, &checkOfCorrectWorkOfStackFunctions);
            secondElement = pop(&head, &checkOfCorrectWorkOfStackFunctions);
            firstElement += secondElement;
            push(&head, firstElement, &checkOfCorrectWorkOfStackFunctions);
            break;
        default:
            number = commandSequence[i] - '0';
            push(&head, number, &checkOfCorrectWorkOfStackFunctions);
            break;
        }
        ++i;
    }
    deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
    return pop(&head, &checkOfCorrectWorkOfStackFunctions);
}

bool checkOfCalculation(char commandSequence[], int expectedResult)
{
    StackElement* head = NULL;
    if (!areTestsPassing(&head))
    {
        printf("Stack's tests failed");
        return -1;
    }
    bool checkOfDivisionByZero = false;
    bool* pointerToCheckOfDivisionByZero = &checkOfDivisionByZero;
    bool checkOfCorrectWork = true;
    return calculateInPostfixForm(commandSequence, pointerToCheckOfDivisionByZero, &checkOfCorrectWork) == expectedResult;
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

int main()
{
    if (!standartTest() || !divisionByZeroTest() || !zeroResultTest())
    {
        printf("Tests failed");
        return -1;
    }
    char commandSequence[30] = { '\0' };
    printf("Enter the sequence of digits and operations (in postfix form): ");
    gets_s(commandSequence, 30);
    bool checkOfDivisionByZero = false;
    bool checkOfCorrectWork = true;
    int const resultOfCalculation = calculateInPostfixForm(commandSequence,
        &checkOfDivisionByZero, &checkOfCorrectWork);
    if (checkOfDivisionByZero)
    {
        printf("\n  Incorrect form: division by zero.\n");
        return -1;
    }
    printf("\nThe calculation result: %d\n", resultOfCalculation);

    //int const result = checkOfBracketsBalance(bracketsSequence, &checkOfCorrectWork);
    if (!checkOfCorrectWork)
    {
        printf("Error from stack's functions");
        return -1;
    }
}
