#include <stdio.h>
#include <stdbool.h>

#define SIZE 14

void insertionSort(int array[], int stopIndex, int startIndex)
{
    for (int i = startIndex + 1; i <= stopIndex; ++i)
    {
        int j = i;
        while (array[j] < array[j - 1] && j >= startIndex + 1)
        {
            int const buffer = array[j - 1];
            array[j - 1] = array[j];
            array[j] = buffer;
            --j;
        }
    }
    return;
}

int findTheSupportElement(int array[], int stopIndex, int startIndex, bool* checkOfSupportElement)
{
    int i = startIndex + 1;
    while (array[i - 1] == array[i] && i <= stopIndex)
    {
        ++i;
    }
    if (i == stopIndex + 1 || array[i] == array[i - 1])
    {
        *checkOfSupportElement = false;
        return 0;
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
    return supportElement;
}

void qSort(int array[], int stopIndex, int startIndex)
{
    if (stopIndex - startIndex <= 8)
    {
        insertionSort(array, stopIndex, startIndex);
        return;
    }
    bool checkOfSupportElement = true;
    int const supportElement = findTheSupportElement(array, stopIndex, startIndex, &checkOfSupportElement);
    if (!checkOfSupportElement)
    {
        return;
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
    qSort(array, lessThanSupportElement - 1, startIndex);
    qSort(array, stopIndex, lessThanSupportElement);
}

bool checkOfCleverQSort(int startedArray[], int lengthOfArray, int sortedArray[])
{
    qSort(startedArray, lengthOfArray - 1, 0);
    for (int i = 0; i < lengthOfArray; ++i)
    {
        if (startedArray[i] != sortedArray[i])
        {
            return false;
        }
    }
    return true;
}

bool testWithFifteenElements()
{
    int startedArray[15] = { 0, 1000, 40, 6, 8, 55, 9, 77, -1000, 30, -10, 555, 2, 3, 78 };
    int sortedArray[15] = { -1000, -10, 0, 2, 3, 6, 8, 9, 30, 40, 55, 77, 78, 555, 1000 };
    return checkOfCleverQSort(startedArray, 15, sortedArray);
}

bool reverseSortingTest()
{
    int startedArray[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    int sortedArray[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    return checkOfCleverQSort(startedArray, 10, sortedArray);
}

bool testOfInsertionSort()
{
    int startedArray[9] = { 1, 4, 6, 9, 8, 90, -10, 0, 23 };
    int sortedArray[9] = { -10, 0, 1, 4, 6, 8, 9, 23, 90 };
    return checkOfCleverQSort(startedArray, 9, sortedArray);
}

bool equalElementsTest()
{
    int startedArray[11] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int sortedArray[11] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    return checkOfCleverQSort(startedArray, 11, sortedArray);
}

int main()
{
    if (!testWithFifteenElements() || !reverseSortingTest() || !testOfInsertionSort() || !equalElementsTest())
    {
        printf("Tests failed");
        return 1;
    }
    printf("Enter fourteen elements to full the array: ");
    int array[SIZE] = { 0 };
    for (int i = 0; i < SIZE; ++i)
    {
        scanf("%d", &array[i]);
    }
    qSort(array, SIZE - 1, 0);
    printf("Receive sorted array: ");
    for (int j = 0; j < SIZE; ++j)
    {
        printf("%d ", array[j]);
    }
    printf("\n");
}