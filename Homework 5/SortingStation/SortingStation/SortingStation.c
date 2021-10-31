#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "C:\Users\Home\source\repos\Space-for-homeworks\Homework 5\Stack\Stack\TestsForStack.h"
#include "C:\Users\Home\source\repos\Space-for-homeworks\Homework 5\Stack\Stack\Stack.h"

bool checkOfBracketsBalance(char bracketsSequence[], StackElement** head)
{
    int i = 0;
    while (bracketsSequence[i] != '\0')
    {
        if (bracketsSequence[i] == '(' || bracketsSequence[i] == ')')
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
            else if (bracketsSequence[i] == '(')
            {
                push(head, bracketsSequence[i]);
            }
        }
        ++i;
    }
    return true;
}

void convertToPostfixForm(char infixFormSequence[], char postfixFormSequence[], StackElement** head, bool* pointerToCheckOfConverting)
{
    if (!checkOfBracketsBalance(infixFormSequence, head))
    {
        *pointerToCheckOfConverting = false;
        return;
    }
    int indexOfInfixFormSequence = 0;
    int indexOfPostfixFormSequence = 0;
    while (infixFormSequence[indexOfInfixFormSequence] != '\0')
    {
        switch (infixFormSequence[indexOfInfixFormSequence])
        {
        case ' ':
            break;
        case '\n':
            break;
        case '(':
            push(head, infixFormSequence[indexOfInfixFormSequence]);
            break;
        case ')':
            while (top(head) != '(')
            {
                postfixFormSequence[indexOfPostfixFormSequence] += pop(head);
                ++indexOfPostfixFormSequence;
                postfixFormSequence[indexOfPostfixFormSequence] += ' ';
                ++indexOfPostfixFormSequence;
            }
            pop(head);
            break;
        case '*':
        case '/':
            while (top(head) == ('*' || '/'))
            {
                postfixFormSequence[indexOfPostfixFormSequence] += pop(head);
                ++indexOfPostfixFormSequence;
                postfixFormSequence[indexOfPostfixFormSequence] += ' ';
                ++indexOfPostfixFormSequence;
            }
            push(head, infixFormSequence[indexOfInfixFormSequence]);
            break;
        case '+':
        case '-':
            while (top(head) == '*' || top(head) == '/' || top(head) == '+' || top(head) == '-')
            {
                postfixFormSequence[indexOfPostfixFormSequence] += pop(head);
                ++indexOfPostfixFormSequence;
                postfixFormSequence[indexOfPostfixFormSequence] += ' ';
                ++indexOfPostfixFormSequence;
            }
            push(head, infixFormSequence[indexOfInfixFormSequence]);
            break;
        default:
            postfixFormSequence[indexOfPostfixFormSequence] += infixFormSequence[indexOfInfixFormSequence];
            ++indexOfPostfixFormSequence;
            postfixFormSequence[indexOfPostfixFormSequence] += ' ';
            ++indexOfPostfixFormSequence;
            break;
        }
        ++indexOfInfixFormSequence;
    }
    while (!isEmpty(*head))
    {
        postfixFormSequence[indexOfPostfixFormSequence] += pop(head);
        ++indexOfPostfixFormSequence;
        postfixFormSequence[indexOfPostfixFormSequence] += ' ';
        ++indexOfPostfixFormSequence;
    }
}

bool checkOfConverting(char infixFormSequence[], char resultString[])
{
    StackElement* head = NULL;
    char postfixFormSequence[30] = { '\0' };
    bool checkOfConverting = true;
    convertToPostfixForm(infixFormSequence, postfixFormSequence, &head, &checkOfConverting);
    return strcmp(resultString, postfixFormSequence) == 0;
}

bool standartTest()
{
    char infixFormSequence[20] = "(8 + 5) * 3 6 - 1";
    char resultString[20] = "8 5 + 3 6 * 1 -";
    return checkOfConverting(infixFormSequence, resultString) == 0;
}

bool testWithDivision()
{
    char infixFormSequence[20] = "((9 + 6) + 4) / 8";
    char resultString[20] = "9 6 + 4 + 8 /";
    return checkOfConverting(infixFormSequence, resultString) == 0;
}

int main()
{
    StackElement* head = NULL;
    if (!areTestsPassing(&head))
    {
        printf("Stack's tests failed");
        return -1;
    }
    if (!standartTest() || !testWithDivision())
    {
        printf("Tests failed");
        return -1;
    }
    printf("Enter the mathematical expression (in infix form): ");
    char infixFormSequence[30] = { '\0' };
    gets_s(infixFormSequence, 30);
    char postfixFormSequence[30] = { '\0' };
    bool checkOfConverting = true;
    convertToPostfixForm(infixFormSequence, postfixFormSequence, &head, &checkOfConverting);
    if (!checkOfConverting)
    {
        printf("\nIncorrect mathematical expression\n");
        return -1;
    }
    printf("\nThe mathematical expression in postfix form: %s\n", postfixFormSequence);
}