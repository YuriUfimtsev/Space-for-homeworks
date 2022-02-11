#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 10

void qSort(int array[], int stopIndex, int startIndex)
{
    if (stopIndex - startIndex == 0)
    {
        return;
    }
    if (stopIndex - startIndex == 1)
    {
        if (array[startIndex] > array[stopIndex])
        {
            int const buffer = array[startIndex];
            array[startIndex] = array[stopIndex];
            array[stopIndex] = buffer;
        }
        return;
    }
    int i = startIndex + 1;
    while (array[i - 1] == array[i] && i <= stopIndex)
    {
        ++i;
    }
    if (i == stopIndex + 1 || array[i] == array[i - 1])
    {
        return;
    }
    int supportElement = 0;
    if (array[i] > array[i - 1])
    {
        supportElement = array[i];
    }
    else
    {
        supportElement = array[i - 1];
    }
    int lessThanSupportElement = startIndex;
    int largerThanSupportElement = stopIndex;
    while (lessThanSupportElement < largerThanSupportElement)
    {
        while (array[lessThanSupportElement] < supportElement && lessThanSupportElement != largerThanSupportElement)
        {
            ++lessThanSupportElement;
        }
        while (array[largerThanSupportElement] >= supportElement && lessThanSupportElement != largerThanSupportElement)
        {
            --largerThanSupportElement;
        }
        if (lessThanSupportElement < largerThanSupportElement)
        {
            int const buffer = array[lessThanSupportElement];
            array[lessThanSupportElement] = array[largerThanSupportElement];
            array[largerThanSupportElement] = buffer;
        }
    }
    i = startIndex;
    while (array[i] < supportElement)
    {
        ++i;
    }
    qSort(array, i - 1, startIndex);
    qSort(array, stopIndex, i);
}

int findTheMostCommonElement(int array[], int lengthOfArray)
{
    qSort(array, lengthOfArray - 1, 0);
    int maxCountOfEqualElements = 0;
    int countOfEqualElements = 1;
    int theMostCommonElement = array[0];
    for (int i = 0; i < lengthOfArray - 1; ++i)
    {
        if (array[i] == array[i + 1])
        {
            ++countOfEqualElements;
        }
        if (countOfEqualElements > maxCountOfEqualElements)
        {
            theMostCommonElement = array[i];
            maxCountOfEqualElements = countOfEqualElements;
        }
        if (array[i] != array[i + 1])
        {
            countOfEqualElements = 1;
        }
    }
    return theMostCommonElement;
}

bool checkOfFindTheMostCommonElement(int array[], int lengthOfArray, int result)
{
    return findTheMostCommonElement(array, lengthOfArray) == result;
}

bool testForSixEqualelements()
{
    int array[6] = { 0, 0, 0, 0, 0, 0 };
    return checkOfFindTheMostCommonElement(array, 6, 0);
}

bool standartTestForFifteenElements()
{
    int array[15] = { 1, -100, 0, 3, 45, 44, 0, 18, 25, 18, 35, 44, 55, 9, 44};
    return checkOfFindTheMostCommonElement(array, 15, 44);
}

bool testWithBorderlineCase()
{
    int array[8] = { 5, 4, 7, 8, 0, 9, 3, 7 };
    return checkOfFindTheMostCommonElement(array, 8, 7);
}

int main(int argc, char* argv[])
{
    if (argc == 2 && strcmp(argv[1], "tests_only") == 0)
    {
        return testForSixEqualelements() && standartTestForFifteenElements()
            && testWithBorderlineCase() ? 0 : -2;
    }
    if (!testForSixEqualelements() || !standartTestForFifteenElements() || !testWithBorderlineCase())
    {
        printf("Tests failed");
        return 1;
    }
    printf("Enter ten elements of array: ");
    int array[SIZE] = { 0 };
    int checkScanf = 0;
    for (int i = 0; i < SIZE; ++i)
    {
        checkScanf = scanf("%d", &array[i]);
    }
    int theMostCommonElement = findTheMostCommonElement(array, SIZE);
    printf("The most common element = %d.\n", theMostCommonElement);
}