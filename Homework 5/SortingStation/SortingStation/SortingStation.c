#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "..\..\Stack\Stack\Stack.h"
#include "..\..\Stack\Stack\TestsForStack.h"

void convertToPostfixForm(char infixFormSequence[], char postfixFormSequence[],
    bool* pointerToCheckOfConverting, bool* checkOfCorrectWork)
{
    StackElement* head = NULL;
    if (!areTestsPassing(&head))
    {
        *checkOfCorrectWork = false;
        return;
    }
    int indexOfInfixFormSequence = 0;
    int indexOfPostfixFormSequence = 0;
    bool checkOfCorrectWorkOfStackFunctions = true;
    while (infixFormSequence[indexOfInfixFormSequence] != '\0')
    {
        switch (infixFormSequence[indexOfInfixFormSequence])
        {
        case ' ':
            break;
        case '\n':
            break;
        case '(':
            push(&head, infixFormSequence[indexOfInfixFormSequence], &checkOfCorrectWorkOfStackFunctions);
            break;
        case ')':
            while (top(&head, &checkOfCorrectWorkOfStackFunctions) != '(')
            {
                postfixFormSequence[indexOfPostfixFormSequence] += pop(&head, &checkOfCorrectWorkOfStackFunctions);
                ++indexOfPostfixFormSequence;
                postfixFormSequence[indexOfPostfixFormSequence] += ' ';
                ++indexOfPostfixFormSequence;
            }
            pop(&head, &checkOfCorrectWorkOfStackFunctions);
            break;
        case '*':
        case '/':
            while (top(&head, &checkOfCorrectWorkOfStackFunctions) == ('*' || '/'))
            {
                postfixFormSequence[indexOfPostfixFormSequence] += pop(&head, &checkOfCorrectWorkOfStackFunctions);
                ++indexOfPostfixFormSequence;
                postfixFormSequence[indexOfPostfixFormSequence] += ' ';
                ++indexOfPostfixFormSequence;
            }
            push(&head, infixFormSequence[indexOfInfixFormSequence], &checkOfCorrectWorkOfStackFunctions);
            break;
        case '+':
        case '-':
            while (top(&head, &checkOfCorrectWorkOfStackFunctions) == '*' || top(&head, &checkOfCorrectWorkOfStackFunctions) == '/' ||
                top(&head, &checkOfCorrectWorkOfStackFunctions) == '+' || top(&head, &checkOfCorrectWorkOfStackFunctions) == '-')
            {
                postfixFormSequence[indexOfPostfixFormSequence] += pop(&head, &checkOfCorrectWorkOfStackFunctions);
                ++indexOfPostfixFormSequence;
                postfixFormSequence[indexOfPostfixFormSequence] += ' ';
                ++indexOfPostfixFormSequence;
            }
            push(&head, infixFormSequence[indexOfInfixFormSequence], &checkOfCorrectWorkOfStackFunctions);
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
    while (!isEmpty(head))
    {
        postfixFormSequence[indexOfPostfixFormSequence] += pop(&head, &checkOfCorrectWorkOfStackFunctions);
        ++indexOfPostfixFormSequence;
        postfixFormSequence[indexOfPostfixFormSequence] += ' ';
        ++indexOfPostfixFormSequence;
    }
}

bool checkOfConverting(char infixFormSequence[], char resultString[])
{
    char postfixFormSequence[30] = { '\0' };
    bool checkOfConverting = true;
    bool checkOfCorrectWork = true;
    convertToPostfixForm(infixFormSequence, postfixFormSequence, &checkOfConverting, &checkOfCorrectWork);
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
    bool checkOfCorrectWork = true;

    convertToPostfixForm(infixFormSequence, postfixFormSequence, &checkOfConverting, &checkOfCorrectWork);
    if (!checkOfConverting)
    {
        printf("\nIncorrect mathematical expression\n");
        return -1;
    }
    printf("\nThe mathematical expression in postfix form: %s\n", postfixFormSequence);
}