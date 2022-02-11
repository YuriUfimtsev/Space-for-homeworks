#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "..\..\Stack\Stack\TestsForStack.h"
#include "..\..\Stack\Stack\Stack.h"

int calculateInPostfixForm(const char commandSequence[], bool* checkOfCorrectWork)
{
    StackElement* head = NULL;
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
                deleteStack(&head, checkOfCorrectWork);
                return -1;
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
                    *checkOfCorrectWork = false;
                    deleteStack(&head, checkOfCorrectWork);
                    return -1000;
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
                deleteStack(&head, checkOfCorrectWork);
                return -1;
            }
            break;
        }
        ++i;
    }
    int const result = pop(&head, &checkOfCorrectWorkOfStackFunctions);
    if (!isEmpty(head))
    {
        *checkOfCorrectWork = false;
        deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
        return -1;
    }
    deleteStack(&head, &checkOfCorrectWorkOfStackFunctions);
    if (!checkOfCorrectWorkOfStackFunctions)
    {
        *checkOfCorrectWork = false;
        return -1;
    }
    return result;
}

bool checkOfCalculation(const char commandSequence[],
    int expectedResult, bool expectedCheckOfCorrectWork)
{
    bool checkOfCorrectWork = true;
    return calculateInPostfixForm(commandSequence, &checkOfCorrectWork)
        == expectedResult && checkOfCorrectWork == expectedCheckOfCorrectWork;
}

bool standartTest()
{
    char commandSequence[19] = { "9 5 * 3 / 9 1 + -" };
    return checkOfCalculation(commandSequence, 5, true);
}

bool divisionByZeroTest()
{
    char commandSequence[19] = { "9 5 * 0 / 9 1 + -" };
    return checkOfCalculation(commandSequence, -1000, false);
}

bool zeroResultTest()
{
    char commandSequence[15] = { "3 5 - 8 + 0 *" };
    return checkOfCalculation(commandSequence, 0, true);
}

bool testOfIncorrectSequence()
{
    char commandSequence[15] = { "3 * 5 - 8 + 0 *" };
    return checkOfCalculation(commandSequence, -1, false);
}

bool testWithOneOperand()
{
    char commandSequence[2] = { "1" };
    return checkOfCalculation(commandSequence, 1, true);
}

int main(int argc, char* argv[])
{
    if (argc == 2 && strcmp(argv[1], "tests_only") == 0)
    {
        return standartTest() && divisionByZeroTest() && zeroResultTest()
            && testOfIncorrectSequence() && testWithOneOperand() ? 0 : -2;
    }
    if (!standartTest() || !divisionByZeroTest()
        || !zeroResultTest() || !testOfIncorrectSequence() || !testWithOneOperand())
    {
        printf("Tests failed");
        return -1;
    }
    char commandSequence[30] = { '\0' };
    printf("Enter the sequence of digits and operations (in postfix form): ");
    gets_s(commandSequence, 30);
    bool checkOfCorrectWork = true;
    int const resultOfCalculation = calculateInPostfixForm(commandSequence, &checkOfCorrectWork);
    if (resultOfCalculation == -1000)
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
