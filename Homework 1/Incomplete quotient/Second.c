#include <stdio.h>
#include <stdlib.h>

void printIncompleteQuotient(int x)
{
    printf("%s %d\n", "The incomplete quotient = ", x);
}

int divide(int dividend, int divisor)
{
    dividend = abs(dividend);
    divisor = abs(divisor);
    if (dividend == 0)
    {
        return 0;
    }
    int count = 1;
    int base = divisor;
    while (divisor < dividend)
    {
        divisor += base;
        ++count;
    }
    if (divisor > dividend)
    {
        --count;
    }
    return count;
}

int main()
{
    int dividend = 0;
    int divisor = 0;
    printf("Enter the dividend, divisor: \n");
    int checkScanf = scanf("%d %d", &dividend, &divisor);
    if (checkScanf != 2)
    {
        printf("We are amazed with your failure");
        return 1;
    }

    if (divisor == 0)
    {
        return printf("The incomplete quotient doesn't exist\n");
    }
    int resultDivide = divide(dividend, divisor);
    if (((dividend * divisor) > 0) && (dividend < 0))
    {
        if ((resultDivide * divisor) == dividend)
        {
            printIncompleteQuotient(resultDivide);
        }
        else
        {
            printIncompleteQuotient(resultDivide + 1);
        }
    }
    else if ((dividend * divisor) < 0)
    {
        if (dividend > 0)
        {
            printIncompleteQuotient(-resultDivide);
        }
        else
        {
            if ((-resultDivide * divisor) == dividend)
            {
                printIncompleteQuotient(-resultDivide);
            }
            else
            {
                printIncompleteQuotient(-resultDivide - 1);
            }
        }
    }
    else
    {
        printIncompleteQuotient(resultDivide);
    }
}
