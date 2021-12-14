#include <stdio.h>
#include <stdbool.h>

enum states {
    fail,
    zero,
    first,
    second,
    third,
    fourth,
    fifth,
    sixth,
    seventh,
    eighth,
    nineth,
    ten,
    eleven,
};

char nextSymbol(const char* string, int* indexOfString)
{
    return string[*indexOfString];
}

bool isDigit(char symbol)
{
    return symbol == '0' || symbol == '1' || symbol == '2' || symbol == '3' || symbol == '4'
        || symbol == '5' || symbol == '6' || symbol == '7' || symbol == '8' || symbol == '9';
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
        switch(state)
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
                if (symbol == '-')
                {
                    state = nineth;
                }
                else
                {
                    state = fail;
                }
                break;
            case nineth:
                if (symbol == 'm')
                {
                    state = ten;
                }
                else
                {
                    state = fail;
                }
                break;
            case ten:
                if (symbol == 'm')
                {
                    state = eleven;
                }
                else
                {
                    state = fail;
                }
                break;
            case eleven:
                if (symbol == 'm')
                {
                    state = eleven;
                }
        }
    }
    return state == eleven;
}


int main()
{
    const char string[12] = "21.B10-mm";
    if (isCorrect(string))
    {
        printf("correct");
    }
    else
    {
        printf("incorrect");
    }
}
