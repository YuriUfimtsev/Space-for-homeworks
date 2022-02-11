#include <stdio.h>
#include <stdbool.h>
#include "Sorting.h"

int findTheSupportElement(int array[], int startIndex, int stopIndex)
{
    int i = startIndex + 1;
    while (array[i - 1] == array[i] && i <= stopIndex)
    {
        ++i;
    }
    return array[i] > array[i - 1] ? array[i] : array[i - 1];
}

bool checkOfSupportElement(int array[], int startIndex, int stopIndex)
{
    int i = startIndex + 1;
    while (array[i - 1] == array[i] && i <= stopIndex)
    {
        ++i;
    }
    return !(i == stopIndex + 1 || array[i] == array[i - 1]);
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
    if (!checkOfSupportElement(array, startIndex, stopIndex))
    {
        return;
    }
    int supportElement = findTheSupportElement(array, startIndex, stopIndex);
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