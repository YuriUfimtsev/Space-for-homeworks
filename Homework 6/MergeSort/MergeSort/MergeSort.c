#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

List* merge(List* firstHalfOfList, List* secondHalfOfList)
{
    List* listForMerging = createList();
    Position* secondPartPosition = first(secondHalfOfList);
    int secondHalfOfListValue = getValue(secondHalfOfList, secondPartPosition);
    for (Position* i = first(firstHalfOfList); !last(i); i = next(i))
    {
        int firstHalfOfListValue = getValue(firstHalfOfList, i);
        while (firstHalfOfListValue >= secondHalfOfListValue && !last(secondPartPosition))
        {
            add(listForMerging, secondHalfOfListValue);
            secondPartPosition = next(secondPartPosition);
            if (!last(secondPartPosition))
            {
                secondHalfOfListValue = getValue(secondHalfOfList, secondPartPosition);
            }
        }
        add(listForMerging, firstHalfOfListValue);
    }
    while (!last(secondPartPosition))
    {
        secondHalfOfListValue = getValue(secondHalfOfList, secondPartPosition);
        add(listForMerging, secondHalfOfListValue);
        secondPartPosition = next(secondPartPosition);
    }
    return listForMerging;
}

List* mergeSort(List* listForSorting)
{
    int const size = sizeOfList(listForSorting);
    if (size > 1)
    {
        List* firstHalfOfList = createList();
        List* secondHalfOfList = createList();
        Position* i = first(listForSorting);
        int j = 0;
        while (j < size / 2)
        {
            add(firstHalfOfList, getValue(listForSorting, i));
            i = next(i);
            ++j;
        }
        while (j < size)
        {
            add(secondHalfOfList, getValue(listForSorting, i));
            i = next(i);
            ++j;
        }
        List* sortedFirstHalfOfList = mergeSort(firstHalfOfList);
        List* sortedSecondHalfOfList = mergeSort(secondHalfOfList);
        List* sortedList = merge(sortedFirstHalfOfList, sortedSecondHalfOfList);
        deleteList(firstHalfOfList);
        deleteList(secondHalfOfList);
        return sortedList;
    }
    return listForSorting;
}

int main()
{
    FILE* data = fopen("Data.txt", "r");
    if (data == NULL)
    {
        printf("File not found");
        return -1;
    }
    List* newList = createList();
    List* sortedList = mergeSort(newList);
    for (Position* i = first(sortedList); !last(i); i = next(i))
    {
        printf("%d ", getValue(sortedList, i));
    }
    deleteList(newList);
    deleteList(sortedList);
    fclose(data);
}
