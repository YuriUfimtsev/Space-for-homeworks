#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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

int binSearch()
{

}

int main()
{
	printf("Enter n (length of array) and k (quantity of random numbers): ");
	int lengthOfArray = 0;
	int checkScanf = scanf("%d", &lengthOfArray);
	int quantityOfRandomNumbers = 0;
	checkScanf = scanf("%d", &quantityOfRandomNumbers);
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
    qSort(array, 0, lengthOfArray - 1);
    for (int i = 0; i < quantityOfRandomNumbers; ++i)
	{
		int randomNumber = -200 + rand() % 250;
	}
}
