#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main()
{
    printf("Enter the number: ");
    int number = 0;
    int checkScanf = scanf("%d", &number);
    if (checkScanf != 1)
    {
        printf("We are amazed with your failure");
        return 1;
    }
    if (number >= 2)
    {
        printf("Prime numbers for %d: 2 ", number);
    }
    else
    {
        printf("There are not prime numbers for this figure\n");
        return 0;
    }
    for (int i = 3; i <= number; i += 2)
    {
        bool checkForSimple = true;
        int sqrtOfI = ceil(sqrt(i));
        for (int j = 3; j <= sqrtOfI; ++j)
        {
            if (i % j == 0)
            {
                checkForSimple = false;
                break;
            }
        }
        if (checkForSimple == true)
        {
            printf("%d ", i);
        }
    }
}
