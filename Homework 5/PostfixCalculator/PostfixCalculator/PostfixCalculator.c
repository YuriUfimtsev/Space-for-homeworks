#include <stdio.h>
#include <stdlib.h>

#include "C:\Users\Home\source\repos\Space-for-homeworks\Homework 5\Stack\Stack\Stack.h"
#include "C:\Users\Home\source\repos\Space-for-homeworks\Homework 5\Stack\Stack\TestsForStack.h"

int calculateInPostfixForm(char commandSequence[], StackElement** head)
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
                printf("Incorrect form: division by zero\n");
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

int main()
{
    StackElement* head = NULL;
    if (!areTestsPassing(&head))
    {
        printf("Tests failed");
        return -1;
    }
    char commandSequence[30] = { '\0' };
    printf("Enter the sequence of digits and operations (in postfix form): ");
    gets_s(commandSequence, 30);
    int const resultOfCalculation = calculateInPostfixForm(commandSequence, &head);
    if (resultOfCalculation == -1)
    {
        return -1;
    }
    printf("\nThe calculation result: %d\n", resultOfCalculation);
}
