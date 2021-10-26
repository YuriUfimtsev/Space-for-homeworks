#include <stdio.h>
#include <stdlib.h>

#include "C:\Users\Home\source\repos\Space-for-homeworks\Homework 5\Stack\Stack\Stack.h"
#include "C:\Users\Home\source\repos\Space-for-homeworks\Homework 5\Stack\Stack\TestsForStack.h"

int calculateInPostfixForm(char commandSequence[], StackElement** head, bool* pointerToCheckOfDivisionByZero)
{
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
            firstElement = pop(head);
            secondElement = pop(head);
            firstElement *= secondElement;
            push(head, firstElement);
            break;
        case '/':
            firstElement = pop(head);
            secondElement = pop(head);
            if (firstElement == 0)
            {
                *pointerToCheckOfDivisionByZero = true;
                return -1;
            }
            firstElement = secondElement / firstElement;
            push(head, firstElement);
            break;
        case '-':
            firstElement = pop(head);
            secondElement = pop(head);
            firstElement = secondElement - firstElement;
            push(head, firstElement);
            break;
        case '+':
            firstElement = pop(head);
            secondElement = pop(head);
            firstElement += secondElement;
            push(head, firstElement);
            break;
        default:
            number = commandSequence[i] - '0';
            push(head, number);
            break;
        }
        ++i;
    }
    return pop(head);
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
    return calculateInPostfixForm(commandSequence, &head, pointerToCheckOfDivisionByZero) == expectedResult;
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
    StackElement* head = NULL;
    if (!areTestsPassing(&head))
    {
        printf("Stack's tests failed");
        return -1;
    }
    if (!standartTest() || !divisionByZeroTest() || !zeroResultTest())
    {
        printf("Tests failed");
        return -1;
    }
    char commandSequence[30] = { '\0' };
    printf("Enter the sequence of digits and operations (in postfix form): ");
    gets_s(commandSequence, 30);
    bool checkOfDivisionByZero = false;
    bool* pointerToCheckOfDivisionByZero = &checkOfDivisionByZero;
    int const resultOfCalculation = calculateInPostfixForm(commandSequence, &head, pointerToCheckOfDivisionByZero);
    if (checkOfDivisionByZero)
    {
        printf("\nIncorrect form: division by zero.\n");
        return -1;
    }
    printf("\nThe calculation result: %d\n", resultOfCalculation);
}
