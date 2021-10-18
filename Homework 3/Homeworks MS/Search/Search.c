#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int* makeAnArray(int lengthOfArray)
{
    return calloc(lengthOfArray, sizeof(int));
}
 
void makeAnArrayOfRandomNumbers(int array[], int lengthOfArray)
{
    srand((unsigned)time(0));
    for (int i = 0; i < lengthOfArray; ++i)
    {
        array[i] = -100 + rand() % 200;
    }
}

int findTheSupportElement(int array[], int stopIndex, int startIndex)
{
    int i = startIndex + 1;
    while (array[i - 1] == array[i] && i <= stopIndex)
    {
        ++i;
    }
    int supportElement = array[i] > array[i - 1] ? array[i] : array[i - 1];
    return supportElement;
}

bool checkOfSupportElement(int array[], int stopIndex, int startIndex)
{
    int i = startIndex + 1;
    while (array[i - 1] == array[i] && i <= stopIndex)
    {
        ++i;
    }
    if (i == stopIndex + 1 || array[i] == array[i - 1])
    {
        return false;
    }
    return true;
}

void qSort(int array[], int startIndex, int stopIndex)
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
    if (!checkOfSupportElement(array, stopIndex, startIndex))
    {
        return;
    }
    int supportElement = findTheSupportElement(array, stopIndex, startIndex);
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
    qSort(array, startIndex, lessThanSupportElement - 1);
    qSort(array, lessThanSupportElement, stopIndex);
}

bool binSearch(int array[], int lengthOfArray, int numberForSearch)
{
    int leftBorder = 0;
    int rightBorder = lengthOfArray - 1;
    while (leftBorder <= rightBorder)
    {
        const int middle = (leftBorder + rightBorder) / 2;
        if (numberForSearch == array[middle])
        {
            return true;
        }
        if (numberForSearch < array[middle])
        {
            rightBorder = middle - 1;
        }
        if (numberForSearch > array[middle])
        {
            leftBorder = middle + 1;
        }
    }
    return false;
}

bool checkOfSearch(int array[], int lengthOfArray, int numberForSearch, bool expectedResult)
{
    qSort(array, 0, lengthOfArray - 1);
    return binSearch(array, lengthOfArray, numberForSearch) == expectedResult;
}

bool standartTrueTest()
{
    int array[8] = { -10, 100, 0, 33, 48, 76, 5, 15 };
    return checkOfSearch(array, 8, 15, true);
}

bool standartFalseTest()
{
    int array[10] = { -30, 45, 66, -28, 9, 15, 0, 99, 83, 10000 };
    return checkOfSearch(array, 10, 21, false);
}

bool equalElementsFalseTest()
{
    int array[5] = { 9, 9, 9, 9, 9 };
    return checkOfSearch(array, 5, 8, false);
}

bool equalElementsTrueTest()
{
    int array[4] = { 0, 0, 0, 0 };
    return checkOfSearch(array, 4, 0, true);
}

int main()
{
    if (!standartTrueTest() || !standartFalseTest() || !equalElementsTrueTest() || !equalElementsFalseTest())
    {
        printf("Tests failed");
        return -1;
    }
    printf("Enter n (length of array) and k (quantity of random numbers): ");
    int lengthOfArray = 0;
    int checkScanf = scanf("%d", &lengthOfArray);
    int quantityOfRandomNumbers = 0;
    scanf("%d", &quantityOfRandomNumbers);
    if (lengthOfArray <= 0 || quantityOfRandomNumbers <= 0)
    {
        printf("Incorrect input!");
        return -1;
    }
    int* array = makeAnArray(lengthOfArray);
    if (array == NULL)
    {
        printf("bad");
        return -1;
    }
    makeAnArrayOfRandomNumbers(array, lengthOfArray);
    printf("array of random elements: ");
    for (int i = 0; i < lengthOfArray; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    qSort(array, 0, lengthOfArray - 1);
    for (int i = 0; i < quantityOfRandomNumbers; ++i)
    {
        const int randomNumber = -200 + rand() % 250;
        if (binSearch(array, lengthOfArray, randomNumber))
        {
            printf("The element %d is in array\n", randomNumber);
        }
        else
        {
            printf("The array doesn't contain element % d\n", randomNumber);
        }
    }
    free(array);
}
