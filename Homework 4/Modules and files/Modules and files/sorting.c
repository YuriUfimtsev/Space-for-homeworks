#include <stdio.h>
#include "Sorting.h"

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