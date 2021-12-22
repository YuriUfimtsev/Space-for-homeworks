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

bool isPointOrE(char symbol)
{
    return symbol == 'E' || symbol == '.';
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

bool testWithInteger()
{

}

int main()
{
    char string[30] = "7676.0E+897\0";
    isCorrect(string);
}

