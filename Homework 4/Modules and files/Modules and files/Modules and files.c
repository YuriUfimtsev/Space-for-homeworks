#include <stdio.h>
#include "Sorting.h"
#include <stdbool.h>
#include <stdlib.h>

int* makeAnArray(int lengthOfArray)
{
    return calloc(lengthOfArray, sizeof(int));
}

int findTheMostCommonElement(int array[], int lengthOfArray)
{
    qSort(array, 0, lengthOfArray - 1);
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

int countNumberOfEntries(FILE *file)
{
    fseek(file, 0, SEEK_SET);
    int counter = 0;
    while (!feof(file))
    {
        fscanf(file, "%*d");
        ++counter;
    }
    fseek(file, 0, SEEK_SET);
    return counter;
}

bool checkOfFindTheMostCommonElement(int array[], int lengthOfArray, int result)
{
    return findTheMostCommonElement(array, lengthOfArray) == result;
}

bool testForSixEqualElements()
{
    int array[6] = { 0, 0, 0, 0, 0, 0 };
    return checkOfFindTheMostCommonElement(array, 6, 0);
}

bool standartTestForFifteenElements()
{
    int array[15] = { 1, -100, 0, 3, 45, 44, 0, 18, 25, 18, 35, 44, 55, 9, 44 };
    return checkOfFindTheMostCommonElement(array, 15, 44);
}

bool testWithBorderlineCase()
{
    int array[8] = { 5, 4, 7, 8, 0, 9, 3, 7 };
    return checkOfFindTheMostCommonElement(array, 8, 7);
}

int main()
{
    if (!testForSixEqualElements() || !standartTestForFifteenElements() || !testWithBorderlineCase())
    {
        printf("Tests failed");
        return 1;
    }
    FILE* file = fopen("Set of Numbers.txt", "r");
    if (file == NULL)
    {
        printf("File not found!");
        return -1;
    }
    int counter = countNumberOfEntries(file);
    int* array = makeAnArray(counter + 1);
    if (array == NULL)
    {
        printf("bad");
        fclose(file);
        return -1;
    }
    for (int i = 0; i < counter + 1; ++i)
    {
        fscanf(file, "%d", &array[i]);
    }
    int theMostCommonElement = findTheMostCommonElement(array, counter + 1);
    printf("The most common element = %d.\n", theMostCommonElement);
    free(array);
    fclose(file);
}
