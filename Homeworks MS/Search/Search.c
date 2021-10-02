#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

void makeAnArrayOFRandomNumbers(int array[], int lengthOfArray)
{
	srand(time(NULL));
	for (int i = 0; i < lengthOfArray; ++i)
	{
		array[i] = -100 + rand() % 200;
	}
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
    qSort(array, startIndex, i - 1);
    qSort(array, i, stopIndex);
}

bool binSearch(int array[], int lengthOfArray, int numberForSearch)
{
    int leftBorder = 0;
    int rightBorder = lengthOfArray - 1;
    while (leftBorder <= rightBorder)
    {
        int middle = (leftBorder + rightBorder) / 2;
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
	checkScanf = scanf("%d", &quantityOfRandomNumbers);
    if (lengthOfArray <= 0 || quantityOfRandomNumbers <= 0)
    {
        printf("Incorrect input!");
        return -1;
    }
	int *array = calloc(lengthOfArray, sizeof(int));
	if (array == NULL)
	{
		printf("bad");
		return -1;
	}
	makeAnArrayOFRandomNumbers(array, lengthOfArray);
	printf("Array of random elements: ");
	for (int i = 0; i < lengthOfArray; ++i)
	{
		printf("%d ", array[i]);
	}
    printf("\n");
    qSort(array, 0, lengthOfArray - 1);
    for (int i = 0; i < quantityOfRandomNumbers; ++i)
	{
		int randomNumber = -200 + rand() % 250;
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
