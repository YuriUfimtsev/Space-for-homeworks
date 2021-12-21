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
};

char nextSymbol(const char* string, int* indexOfString)
{
    return string[*indexOfString];
}

bool isDigit(char symbol)
{
    return symbol >= '0' || symbol <= '9';
}

bool isCorrect(const char* string)
{
    enum states state;
    char symbol = ' ';
    state = zero;
    int indexOFString = 0;
    while (state != fail && state != eleven)
    {
        symbol = nextSymbol(string, &indexOFString);
        ++indexOFString;
        switch (state)
        {
        case zero:
            if (isDigit(symbol))
            {
                state = first;
            }
            else
            {
                state = false;
            }
            break;
        case first:
            if (isDigit(symbol))
            {
                state = second;
            }
            else
            {
                state = fail;
            }
            break;
        case second:
            if (symbol == '.')
            {
                state = third;
            }
            else
            {
                state = fail;
            }
            break;
        case third:
            if (symbol == 'B')
            {
                state = fourth;
            }
            else if (symbol == 'M')
            {
                state = fifth;
            }
            else if (symbol == 'S')
            {
                state = sixth;
            }
            else
            {
                state = fail;
            }
            break;
        case fourth:
            if (isDigit(symbol))
            {
                state = seventh;
            }
            else
            {
                state = fail;
            }
            break;
        case fifth:
            if (isDigit(symbol))
            {
                state = seventh;
            }
            else
            {
                state = fail;
            }
            break;
        case sixth:
            if (isDigit(symbol))
            {
                state = seventh;
            }
            else
            {
                state = fail;
            }
            break;
        case seventh:
            if (isDigit(symbol))
            {
                state = eighth;
            }
            else
            {
                state = fail;
            }
            break;
        case eighth:
            state = symbol == '-' ? nineth : fail;
}

int main()
{

}

