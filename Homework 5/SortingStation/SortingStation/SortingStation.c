#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "..\..\Stack\Stack\Stack.h"
#include "..\..\Stack\Stack\TestsForStack.h"

void addInTheSequenceWithSpace(char sequence[], int* indexOfSequence, const char elementForAdding)
{
    sequence[*indexOfSequence] += elementForAdding;
    ++(*indexOfSequence);
    sequence[*indexOfSequence] += ' ';
    ++(*indexOfSequence);
}

bool convertToPostfixForm(const char infixFormSequence[], char postfixFormSequence[], const char lengthOfPostfixFormSequence)
{
    StackElement* head = NULL;
    int indexOfInfixFormSequence = 0;
    int indexOfPostfixFormSequence = 0;
    int counterOfNumbers = 0;
    int counterOfOperators = 0;
    bool checkOfCorrectWorkOfStackFunctions = true;
    bool checkOfCorrectWorkOfTop = true;
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
            while (checkOfCorrectWorkOfStackFunctions && top(&head, &checkOfCorrectWorkOfTop) != '(' )
            {
                const char elementForAdding = pop(&head, &checkOfCorrectWorkOfStackFunctions);
                if (indexOfPostfixFormSequence > lengthOfPostfixFormSequence - 3)
                {
                    deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
                    return false;
                }
                addInTheSequenceWithSpace(postfixFormSequence, &indexOfPostfixFormSequence, elementForAdding);
            }
            pop(&head, &checkOfCorrectWorkOfStackFunctions);
            break;
        case '*':
        case '/':
            while (top(&head, &checkOfCorrectWorkOfTop) == '*' ||
                top(&head, &checkOfCorrectWorkOfTop) == '/')
            {
                const char elementForAdding = pop(&head, &checkOfCorrectWorkOfStackFunctions);
                if (indexOfPostfixFormSequence > lengthOfPostfixFormSequence - 3)
                {
                    deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
                    return false;
                }
                addInTheSequenceWithSpace(postfixFormSequence, &indexOfPostfixFormSequence, elementForAdding);
            }
            push(&head, infixFormSequence[indexOfInfixFormSequence], &checkOfCorrectWorkOfStackFunctions);
            ++counterOfOperators;
            break;
        case '+':
        case '-':
            while (top(&head, &checkOfCorrectWorkOfTop) == '*' || top(&head, &checkOfCorrectWorkOfTop) == '/' ||
                top(&head, &checkOfCorrectWorkOfTop) == '+' || top(&head, &checkOfCorrectWorkOfTop) == '-')
            {
                const char elementForAdding = pop(&head, &checkOfCorrectWorkOfStackFunctions);
                if (indexOfPostfixFormSequence > lengthOfPostfixFormSequence - 3)
                {
                    deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
                    return false;
                }
                addInTheSequenceWithSpace(postfixFormSequence, &indexOfPostfixFormSequence, elementForAdding);
            }
            push(&head, infixFormSequence[indexOfInfixFormSequence], &checkOfCorrectWorkOfStackFunctions);
            ++counterOfOperators;
            break;
        default:
            if (indexOfPostfixFormSequence > lengthOfPostfixFormSequence - 3)
            {
                deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
                return false;
            }
            addInTheSequenceWithSpace(postfixFormSequence, &indexOfPostfixFormSequence,
                infixFormSequence[indexOfInfixFormSequence]);
            ++counterOfNumbers;
            break;
        }
        if (!checkOfCorrectWorkOfStackFunctions)
        {
            deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
            return false;
        }
        ++indexOfInfixFormSequence;
    }
    if (counterOfNumbers - (counterOfOperators + 1) != 0)
    {
        deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
        return false;
    }
    while (!isEmpty(head))
    {
        const char elementForAdding = pop(&head, &checkOfCorrectWorkOfStackFunctions);
        if (elementForAdding == '(' || !checkOfCorrectWorkOfStackFunctions)
        {
            deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
            return false;
        }
        if (indexOfPostfixFormSequence > lengthOfPostfixFormSequence - 3)
        {
            deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
            return false;
        }
        addInTheSequenceWithSpace(postfixFormSequence, &indexOfPostfixFormSequence, elementForAdding);
    }
    deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
    return true;
}

bool checkOfConverting(const char infixFormSequence[], const char resultString[], bool* checkOfCorrectnessOfSequence)
{
    char postfixFormSequence[30] = { '\0' };
    bool const resultOfConverting = convertToPostfixForm(infixFormSequence, postfixFormSequence, 30);
    if (!resultOfConverting)
    {
        *checkOfCorrectnessOfSequence = false;
    }
    return strcmp(resultString, postfixFormSequence) == 0;
}

bool standartTest()
{
    char infixFormSequence[20] = "(8 + 5) * 6 - 1";
    char resultString[20] = "8 5 + 6 * 1 - ";
    bool checkOfCorrectnessOfSequence = true;
    return checkOfConverting(infixFormSequence, resultString, &checkOfCorrectnessOfSequence)
        && checkOfCorrectnessOfSequence;
}

bool testWithDivision()
{
    char infixFormSequence[20] = "((9 + 6) + 4) / 8";
    char resultString[20] = "9 6 + 4 + 8 / ";
    bool checkOfCorrectnessOfSequence = true;
    return checkOfConverting(infixFormSequence, resultString, &checkOfCorrectnessOfSequence) && checkOfCorrectnessOfSequence;
}

bool testWithIncorrectSequence()
{
    char infixFormSequence[20] = "(8 + 5) * 3 6 - 1";
    char resultString[20] = "8 5 + 3 6 * 1 - ";
    bool checkOfCorrectnessOfSequence = true;
    return !(checkOfConverting(infixFormSequence, resultString, &checkOfCorrectnessOfSequence) && checkOfCorrectnessOfSequence);
}

int main()
{
    StackElement* head = NULL;
    bool checkOfCorrectWork = true;
    if (!areTestsPassing(&head))
    {
        printf("Stack's tests failed");
        return -1;
    }
    deleteStack(&head, &checkOfCorrectWork);
    if (!checkOfCorrectWork)
    {
        printf("Error with stack deletion");
        return -1;
    }
    if (!standartTest() || !testWithDivision() || !testWithIncorrectSequence())
    {
        printf("Tests failed");
        return -1;
    }
    printf("Enter the mathematical expression (in infix form): ");
    char infixFormSequence[30] = { '\0' };
    gets_s(infixFormSequence, 30);
    char postfixFormSequence[30] = { '\0' };
    bool resultOfConvertingInPostfixForm = true;
    resultOfConvertingInPostfixForm = convertToPostfixForm(infixFormSequence, postfixFormSequence, 30);
    if (!resultOfConvertingInPostfixForm)
    {
        printf("\nIncorrect mathematical expression or overflow error\n");
        return -1;
    }
    printf("\nThe mathematical expression in postfix form: %s\n", postfixFormSequence);
}