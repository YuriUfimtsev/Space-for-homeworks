#pragma warning (disable: 4996)

#define MAX_SIZE_OF_ARRAY 1000

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//int* makeLargerArray(const int* currentArray, const int sizeOfNewArray, const int sizeOfCurrentArray)
//{
//    int* newArray = calloc(sizeOfNewArray, sizeof(int));
//    for (int i = 0; i < sizeOfCurrentArray; ++i)
//    {
//        newArray[i] = currentArray[i];
//    }
//    free(currentArray);
//    return newArray;
//}

int* makeArrayFromNumbers(int* arrayOfCounting, int* sizeOfArray)
{
    int newNumber = 1;
    int arrayOfNumbers[MAX_SIZE_OF_ARRAY] = { 0 };
    while (newNumber > 0)
    {
        scanf("%d ", &newNumber);
        bool isNumberInArray = false;
        for (int i = 0; i < *sizeOfArray; ++i)
        {
            if (arrayOfNumbers[i] == newNumber)
            {
                isNumberInArray = true;
                arrayOfCounting[i] += 1;
            }
        }
        if (!isNumberInArray)
        {
            arrayOfNumbers[*sizeOfArray] = newNumber;
            arrayOfCounting[*sizeOfArray] += 1;
            ++(*sizeOfArray);
        }
    }
    return *arrayOfNumbers;
}

void sortArray(int* arrayForSorting, const int sizeOfArrayForSorting)
{
    for (int j = 1; j < sizeOfArrayForSorting; ++j)
    {
        bool isSort = false;
        for (int i = 0; i < sizeOfArrayForSorting - j -1; ++i)
        {
            if (arrayForSorting[i] > arrayForSorting[i + 1])
            {
                const int buffer = arrayForSorting[i];
                arrayForSorting[i] = arrayForSorting[i + 1];
                arrayForSorting[i + 1] = arrayForSorting[i];
                isSort = true;
            }
        }
        if (!isSort)
        {
            break;
        }
    }
}

int main()
{
    int arrayOfCounting[MAX_SIZE_OF_ARRAY] = { 0 };
    int sizeOfArray = 0;
    int* arrayOfNumbers = makeArrayFromNumbers(&arrayOfCounting, &sizeOfArray);
    sortArray(arrayOfNumbers, sizeOfArray);
    for (int i = 0; i < sizeOfArray; ++i)
    {
        printf(" number %d appears %d times,", arrayOfNumbers[i], arrayOfCounting[i]);
    }

}

