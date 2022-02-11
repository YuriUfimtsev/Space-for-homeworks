#include <stdio.h>
#include <time.h>
#include <stdbool.h>

int fibonacciRecursion(startNumber)
{
    if (startNumber < 0)
    {
        return 0;
    }
    if ((startNumber == 0) || (startNumber == 1))
    {
        return 1;
    }
    else
    {
        return fibonacciRecursion(startNumber - 1) + fibonacciRecursion(startNumber - 2);
    }
}

int fibonacciIterative(startNumber)
{
    if (startNumber < 0)
    {
        return 0;
    }
    int zeroElement = 1;
    int firstElement = 1;
    int buffer = zeroElement;
    for (int i = 0; i < startNumber; ++i)
    {
        buffer = zeroElement;
        zeroElement = firstElement;
        firstElement = zeroElement + buffer;
    }
    return zeroElement;
}

bool fibonacciNumbersTest(startNumber, expectedResult)
{
    return (fibonacciRecursion(startNumber) == expectedResult) && (fibonacciIterative(startNumber) == expectedResult);
}

bool testZeroNumber()
{
    return fibonacciNumbersTest(0, 1);
}

bool testFirstNumber()
{
    return fibonacciNumbersTest(1, 1);
}

bool testNegativeNumber()
{
    return fibonacciNumbersTest(-1, 0);
}

bool testFifthNumber()
{
    return fibonacciNumbersTest(5, 8);
}

bool testTenthNumber()
{
    return fibonacciNumbersTest(10, 89);
}

int main()
{
    if (!testZeroNumber() || !testFirstNumber() || !testNegativeNumber() || !testFifthNumber() || !testTenthNumber())
    {
        printf("Tests failed\n");
        return 0;
    }

    printf("Enter the start number: ");
    int fibonacciNumber = 0;
    int const checkScanf = scanf("%d", &fibonacciNumber);
    if (checkScanf != 1)
    {
        printf("We are amazed with your failure");
        return 0;
    }

    printf("The Fibonacci number for it (recursion method): ");
    clock_t const startRecursion = clock();
    int resultFibonacci = fibonacciRecursion(fibonacciNumber);
    if (resultFibonacci == 0)
    {
        printf("doesn't exist...\nYou have entered a negative number!\n");
        return 0;
    }
    printf("%d\n", resultFibonacci);
    clock_t const finishRecursion = clock();
    double const durationRecursion = (float) (finishRecursion - startRecursion) / CLOCKS_PER_SEC;
    printf("Time for this method: %1.3f seconds\n", durationRecursion);

    printf("The Fibonacci number for it (iterative method): ");
    clock_t const startIterative = clock();
    resultFibonacci = fibonacciIterative(fibonacciNumber);
    if (resultFibonacci == 0)
    {
        printf("doesn't exist...\nYou have entered a negative number!\n");
        return 0;
    }
    printf("%d\n", fibonacciIterative(fibonacciNumber));
    clock_t const finishIterative = clock();
    double const durationIterative = (float) (finishIterative - startIterative) / CLOCKS_PER_SEC;
    printf("Time for this method: %1.3f seconds\n", durationIterative);
}
