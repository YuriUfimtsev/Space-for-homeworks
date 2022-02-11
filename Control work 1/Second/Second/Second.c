#include <stdio.h>
#include <stdbool.h>

#define SIZE 10

void selectionSort(int array[], int lengthOfArray)
{
    for (int i = 0; i < lengthOfArray; ++i)
    {
        int indexOfMinElement = i;
        int minElement = array[i];
        for (int j = i + 1; j < lengthOfArray; ++j)
        {
            if (array[j] <= minElement)
            {
                indexOfMinElement = j;
                minElement = array[j];
            }
        }
        if (indexOfMinElement != i)
        {
            int buffer = array[indexOfMinElement];
            array[indexOfMinElement] = array[i];
            array[i] = buffer;
        }
    }
}

bool checkOfSort(int array[], int lengthOfArray, int expectedArray[])
{
    bool checkOfEqual = true;
    selectionSort(array, lengthOfArray);
    for (int i = 0; i < lengthOfArray; ++i)
    {
        if (array[i] != expectedArray[i])
        {
            checkOfEqual = false;
            break;
        }
    }
    return checkOfEqual;
}

bool standartTest()
{
    int array[5] = { 9, 8, 6, 45, 1 };
    int expectedArray[5] = { 1, 6, 8, 9, 45 };
    return checkOfSort(array, 5, expectedArray);
}

bool reverseSortingTest()
{
    int array[6] = { 10, 9, 8, 7, 6, 5 };
    int expectedArray[6] = { 5, 6, 7, 8, 9, 10 };
    return checkOfSort(array, 6, expectedArray);
}

bool equalElementsTest()
{
    int array[5] = { 0, 0, 0, 0, 0 };
    int expectedArray[5] = { 0, 0, 0, 0, 0 };
    return checkOfSort(array, 5, expectedArray);
}

int main()
{
    if (!standartTest() || !reverseSortingTest() || !equalElementsTest())
    {
        printf("Tests failed");
        return -1;
    }
    int array[SIZE] = { 0 };
    printf("Enter the 10 elements of starting array: ");
    for (int i = 0; i < SIZE; ++i)
    {
        int checkScanf = scanf("%d", &array[i]);
    }
    selectionSort(array, SIZE);
    printf("Sorted array: ");
    for (int i = 0; i < SIZE; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
