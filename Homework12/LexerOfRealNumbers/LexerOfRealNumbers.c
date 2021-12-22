#pragma warning(disable: 4996 6031)

#include <stdio.h>
#include <stdbool.h>

enum States {
    startState,
    seenDigit,
    seenPoint,
    seenDigitAfterPoint,
    seenE,
    seenPlusOrMinus,
    seenDigitAfterE,
    fail,
    admittingState,
};

char nextSymbol(const char* string, int* indexOfString)
{
    return string[*indexOfString];
}

bool isDigit(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

bool isCorrect(const char* string)
{
    enum States state;
    char symbol = ' ';
    state = startState;
    int indexOFString = 0;
    while (state != fail && state != admittingState)
    {
        symbol = nextSymbol(string, &indexOFString);
        ++indexOFString;
        switch (state)
        {
        case startState:
            state = isDigit(symbol) ? seenDigit : fail;
            break;
        case seenDigit:
            state = isDigit(symbol) ? seenDigit : fail;
            if (symbol == 'E')
            {
                state = seenE;
            }
            if (symbol == '.')
            {
                state = seenPoint;
            }
            if (symbol == '\0')
            {
                state = admittingState;
            }
            break;
        case seenPoint:
            state = isDigit(symbol) ? seenDigitAfterPoint : fail;
            break;
        case seenDigitAfterPoint:
            state = isDigit(symbol) ? seenDigitAfterPoint : fail;
            if (symbol == 'E')
            {
                state = seenE;
            }
            if (symbol == '\0')
            {
                state = admittingState;
            }
            break;
        case seenE:
            state = isDigit(symbol) ? seenDigitAfterE : fail;
            if (symbol == '+' || symbol == '-')
            {
                state = seenPlusOrMinus;
            }
            break;
        case seenPlusOrMinus:
            state = isDigit(symbol) ? seenDigitAfterE : fail;
            break;
        case seenDigitAfterE:
            state = isDigit(symbol) ? seenDigitAfterE : fail;
            if (symbol == '\0')
            {
                state = admittingState;
            }
            break;
        }
    }
    return state == admittingState;
}

bool lexerTests(const char* string, const bool expectedResult)
{
    return isCorrect(string) == expectedResult;
}

bool testOfInteger()
{
    return lexerTests("567567567576\0", true);
}

bool testWithPointAndE()
{
    return lexerTests("78778.899E7\0", true);
}

bool testWithPlusMinus()
{
    return lexerTests("78778899E+7\0", true);
}

bool falseTest()
{
    return lexerTests("657,6E6687A\0", false);
}

bool areTestsPassing()
{
    return testOfInteger() && testWithPointAndE() && testWithPlusMinus() && falseTest();
}

int main()
{
    if (!areTestsPassing())
    {
        printf("Tests failed");
        return -1;
    }
    printf("Enter the string (less than 40 symbols):");
    char string[41] = { '\0' };
    scanf("%s", &string);
    if (isCorrect(string))
    {
        printf("\nIt is a real number");
        return 0;
    }
    printf("It isn't a real number :(");
}

