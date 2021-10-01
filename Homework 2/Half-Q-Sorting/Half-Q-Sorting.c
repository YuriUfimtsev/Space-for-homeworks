#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

void sort (int array[], int length)
{
    int lessThanFirstElement = 1;
    int largerThanFirstElement = length - 1;
    int const theFirstElement = array[0];
    while (lessThanFirstElement < largerThanFirstElement)
    {
        while (array[lessThanFirstElement] < theFirstElement && lessThanFirstElement != largerThanFirstElement)
        {
            ++lessThanFirstElement;
        }
        while (array[largerThanFirstElement] >= theFirstElement && lessThanFirstElement != largerThanFirstElement)
        {
            --largerThanFirstElement;
        }
        if (lessThanFirstElement < largerThanFirstElement)
        {
            int buffer = array[lessThanFirstElement];
            array[lessThanFirstElement] = array[largerThanFirstElement];
            array[largerThanFirstElement] = buffer;
        }
    }
}

bool checkOfSort(int array[], int lengthOfArray, int numbersLessThanFirst, int numbersLargeThanFirst)
{
    int resultOfNumbersLessThanFirst = 0;
    int resultOfNumbersLargeThanFirst = 0;
    int const theFirstElement = array[0];
    sort(array, lengthOfArray);
    int i = 1;
    while (array[i] < theFirstElement && i < lengthOfArray) 
    {
        ++resultOfNumbersLessThanFirst;
        ++i;
    }
    while (i < lengthOfArray)
    {
        if (array[i] >= theFirstElement)
        {
            ++resultOfNumbersLargeThanFirst;
        }
        ++i;
    }
    return (resultOfNumbersLessThanFirst == numbersLessThanFirst && resultOfNumbersLargeThanFirst == numbersLargeThanFirst);
}

bool testWithTenElements()
{
    int array[10] = { 4, 5, 8, 2, 1, 0, 9, 5, 29, 3 };
    return checkOfSort(array, 10, 4, 5);
}

bool testWithFiveElements()
{
    int array[5] = { 30, 10, 3, 9, 18 };
    return checkOfSort(array, 5, 4, 0);
}

bool testWithNegativeNumbers()
{
    int array[6] = { 10, -10, 3, 59, -20, 0 };
    return checkOfSort(array, 6, 4, 1);
}

bool testWithSixZeros()
{
    int array[6] = { 0, 0, 0, 0, 0, 0 };
    return checkOfSort(array, 6, 0, 5);
}

int main()
{
    if (!testWithTenElements() || !testWithFiveElements() || !testWithNegativeNumbers() || !testWithSixZeros())
    {
        printf("Tests failed\n");
        return 0;
    }
    printf("Start array:\n");
    int array[SIZE] = { 0 };
    for (int i = 0; i < SIZE; ++i)
    {
        array[i] = rand() % 100;
        printf(" %d ", array[i]);
    }
    sort(array, SIZE);
    printf("\nFinished array:\n");
    for (int i = 0; i < SIZE; ++i)
    {
        printf(" %d ", array[i]);
    }
    printf("\n");
}
