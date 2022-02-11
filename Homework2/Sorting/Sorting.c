#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>

#define SIZE 20

void sortWithBubble(int lengthOfArray, int array[])
{
    for (int i = 0; i < lengthOfArray; ++i)
    {
        for (int j = lengthOfArray - 1; j > i; --j)
        {
            if (array[j - 1] > array[j])
            {
                int buffer = array[j - 1];
                array[j - 1] = array[j];
                array[j] = buffer;
            }
        }
    }
}

void sortByCounting(int lengthOfArray, int array[])
{
    int minElement = array[0];
    int maxElement = array[0];
    for (int i = 0; i < lengthOfArray; ++i)
    {
        if (array[i] > maxElement)
        {
            maxElement = array[i];
        }
        if (array[i] < minElement)
        {
            minElement = array[i];
        }
    }
    int const sizeOfAdditionalArray = maxElement - minElement + 1;
    int *additionalArray = calloc(sizeOfAdditionalArray, sizeof(int));
    if (additionalArray == NULL)
    {
        return;
    }
    for (int i = 0; i < lengthOfArray; ++i)
    {
        ++additionalArray[array[i] - minElement];
    }
    int indexOfArray = 0;
    for (int i = 0; i < sizeOfAdditionalArray; ++i)
    {
        while (additionalArray[i] > 0)
        {
            array[indexOfArray] = i + minElement;
            --additionalArray[i];
            ++indexOfArray;
        }
    }
    free(additionalArray);
}

bool sortingTest(int arrayForCounting[], int expectedArray[])
{
    int arrayForBubble[5] = { 0 };
    for (int i = 0; i < 5; ++i)
    {
        arrayForBubble[i] = arrayForCounting[i];
    }
    sortWithBubble(5, arrayForBubble);
    sortByCounting(5, arrayForCounting);
    bool checkOfEquality = true;
    for (int i = 0; i < 5; ++i)
    {
        if (!(arrayForBubble[i] == expectedArray[i]) || !(arrayForCounting[i] == expectedArray[i]))
        {
            checkOfEquality = false;
            break;
        }
    }
    return checkOfEquality;
}

bool standartTest()
{
    int arrayForCounting[5] = { 35, 40, 12, 100, 10 };
    int expectedArray[5] = { 10, 12, 35, 40, 100 };
    return sortingTest(arrayForCounting, expectedArray);
}

bool testWithNegativeNumbers()
{
    int arrayForCounting[5] = { 100, -10, 0, -100, 10 };
    int expectedArray[5] = { -100, -10, 0, 10, 100 };
    return sortingTest(arrayForCounting, expectedArray);
}

bool testWithSameNumbers()
{
    int arrayForCounting[5] = { 30, 27, 40, 27, 5 };
    int expectedArray[5] = { 5, 27, 27, 30, 40 };
    return sortingTest(arrayForCounting, expectedArray);
}

bool testWithZeros()
{
    int arrayForCounting[5] = { 0, 0, 0, 0, 0 };
    int expectedArray[5] = { 0, 0, 0, 0, 0 };
    return sortingTest(arrayForCounting, expectedArray);
}

int main()
{
    if (!standartTest() || !testWithNegativeNumbers() || !testWithSameNumbers() || !testWithZeros())
    {
        printf("Tests failed\n");
        return 0;
    }
    printf("Starting array for sorting: ");
    int arrayForCounting[SIZE] = { 0 };
    int arrayForBubble[SIZE] = { 0 };
    for (int i = 0; i < SIZE; ++i)
    {
        arrayForCounting[i] = rand() % 1000;
        arrayForBubble[i] = arrayForCounting[i];
        printf("%d ", arrayForCounting[i]);
    }
    sortByCounting(SIZE, arrayForCounting);
    printf("\nArray after sorting by counting: ");
    for (int i = 0; i < SIZE; ++i)
    {
        printf("%d ", arrayForCounting[i]);
    }
    sortWithBubble(SIZE, arrayForBubble);
    printf("\nArray after sorting with bubble:  ");
    for (int i = 0; i < SIZE; ++i)
    {
        printf("%d ", arrayForBubble[i]);
    }
    printf("\n");
}
