#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "..\..\Stack\Stack\Stack.h"
#include "..\..\Stack\Stack\TestsForStack.h"

void addInTheSequence(char sequence[], int* indexOfSequence, const char elementForAdding)
{
    sequence[*indexOfSequence] += elementForAdding;
    ++(*indexOfSequence);
}

void convertToPostfixForm(const char infixFormSequence[], char postfixFormSequence[],
    bool* checkOfConverting, bool* checkOfCorrectWork)
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
            while (checkOfCorrectWorkOfStackFunctions &&
                top(&head, &checkOfCorrectWorkOfStackFunctions) != '(' )
            {
                const char elementForAdding = pop(&head, &checkOfCorrectWorkOfStackFunctions);
                addInTheSequence(postfixFormSequence, &indexOfPostfixFormSequence, elementForAdding);
                addInTheSequence(postfixFormSequence, &indexOfPostfixFormSequence, ' ');
            }
            if (!checkOfCorrectWorkOfStackFunctions)
            {
                *checkOfCorrectWork = false;
                return;
            }
            pop(&head, &checkOfCorrectWorkOfStackFunctions);
            break;
        case '*':
        case '/':
            while (top(&head, &checkOfCorrectWorkOfStackFunctions) == '*' ||
                top(&head, &checkOfCorrectWorkOfStackFunctions) == '/')
            {
                const char elementForAdding = pop(&head, &checkOfCorrectWorkOfStackFunctions);
                addInTheSequence(postfixFormSequence, &indexOfPostfixFormSequence, elementForAdding);
                addInTheSequence(postfixFormSequence, &indexOfPostfixFormSequence, ' ');
            }
            push(&head, infixFormSequence[indexOfInfixFormSequence], &checkOfCorrectWorkOfStackFunctions);
            break;
        case '+':
        case '-':
            while (top(&head, &checkOfCorrectWorkOfStackFunctions) == '*' || top(&head, &checkOfCorrectWorkOfStackFunctions) == '/' ||
                top(&head, &checkOfCorrectWorkOfStackFunctions) == '+' || top(&head, &checkOfCorrectWorkOfStackFunctions) == '-')
            {
                const char elementForAdding = pop(&head, &checkOfCorrectWorkOfStackFunctions);
                addInTheSequence(postfixFormSequence, &indexOfPostfixFormSequence, elementForAdding);
                addInTheSequence(postfixFormSequence, &indexOfPostfixFormSequence, ' ');
            }
            push(&head, infixFormSequence[indexOfInfixFormSequence], &checkOfCorrectWorkOfStackFunctions);
            break;
        default:
            addInTheSequence(postfixFormSequence, &indexOfPostfixFormSequence, infixFormSequence[indexOfInfixFormSequence]);
            addInTheSequence(postfixFormSequence, &indexOfPostfixFormSequence, ' ');
            break;
        }
        ++indexOfInfixFormSequence;
    }
    while (!isEmpty(head))
    {
        const char elementForAdding = pop(&head, &checkOfCorrectWorkOfStackFunctions);
        if (elementForAdding == '(')
        {
            *checkOfCorrectWork = false;
            return;
        }
        addInTheSequence(postfixFormSequence, &indexOfPostfixFormSequence, elementForAdding);
        addInTheSequence(postfixFormSequence, &indexOfPostfixFormSequence, ' ');
    }
    deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
}

bool checkOfConverting(const char infixFormSequence[], const char resultString[])
{
    char postfixFormSequence[30] = { '\0' };
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
    if (!checkOfCorrectWork)
    {
        printf("\nIncorrect mathematical expression\n");
        return -1;
    }
    if (!checkOfConverting)
    {
        printf("\nIncorrect mathematical expression\n");
        return -1;
    }
    printf("\nThe mathematical expression in postfix form: %s\n", postfixFormSequence);
}