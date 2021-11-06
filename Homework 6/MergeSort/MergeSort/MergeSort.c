#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

void helpForMerge(List* baseList, List* listForMerging, Position* firstPartPosition, 
    Position* secondPartPosition, int stopIndex)
{
    int firstValue = getValue(baseList, firstPartPosition);
    int secondValue = getValue(baseList, secondPartPosition);
    while (firstValue >= secondValue)
    {
        add(listForMerging, secondValue);
        secondPartPosition = next(secondPartPosition);
        secondValue = getValue(baseList, secondPartPosition);
    }
    add(listForMerging, firstValue);
    int indexOfSecondPartPosition = indexFromPosition(baseList, secondPartPosition);
    while (indexOfSecondPartPosition != stopIndex)
    {
        add(listForMerging, secondValue);
        secondPartPosition = next(secondPartPosition);
        secondValue = getValue(baseList, secondPartPosition);
        indexOfSecondPartPosition = indexFromPosition(baseList, secondPartPosition);
    }
    add(listForMerging, secondValue);
}

//List* merge(List* firstPartForMerging, List* secondPartForMerging)
//{
//    List* listForMerging = createList();
//    Position* firstPartPosition = first(firstPartForMerging);
//    Position* secondPartPosition = first(secondPartForMerging);
//    while (!last(firstPartPosition) && !last(secondPartPosition))
//    {
//        int const firstValue = getValue(firstPartForMerging, firstPartPosition);
//        int const secondValue = getValue(secondPartForMerging, secondPartPosition);
//        if (firstValue >= secondValue)
//        {
//            add(listForMerging, secondValue);
//            secondPartPosition = next(secondPartPosition);
//        }
//        else
//        {
//            add(listForMerging, firstValue);
//            firstPartPosition = next(firstPartPosition);
//        }
//    }
//    if (last(firstPartPosition) && last(secondPartPosition))
//    {
//        int const firstValue = getValue(firstPartForMerging, firstPartPosition);
//        int const secondValue = getValue(secondPartForMerging, secondPartPosition);
//        if (firstValue >= secondValue)
//        {
//            add(listForMerging, secondValue);
//            add(listForMerging, firstValue);
//        }
//        else
//        {
//            add(listForMerging, firstValue);
//            add(listForMerging, secondValue);
//        }
//    }
//    else if (last(firstPartPosition))
//    {
//        helpForMerge(firstPartForMerging, secondPartForMerging, 
//            listForMerging, firstPartPosition, secondPartPosition);
//    }
//    else if (last(secondPartPosition))
//    {
//        helpForMerge(secondPartForMerging, firstPartForMerging,
//            listForMerging, secondPartPosition, firstPartPosition);
//    }
//    deleteList(firstPartForMerging);
//    deleteList(secondPartForMerging);
//    return listForMerging;
//}

List* merge(List* baseList, int startIndex, int listBorder, int stopIndex)
{
    List* listForMerging = createList();
    Position* firstPartPosition = getPositionFromIndex(baseList, startIndex);
    Position* secondPartPosition = getPositionFromIndex(baseList, listBorder);
    int indexOfFirstPartPosition = indexFromPosition(baseList, firstPartPosition);
    int indexOfSecondPartPosition = indexFromPosition(baseList, secondPartPosition);
    while (indexOfFirstPartPosition != listBorder - 1 && indexOfSecondPartPosition != stopIndex)
    {
        int const firstvalue = getValue(baseList, firstPartPosition);
        int const secondvalue = getValue(baseList, secondPartPosition);
        if (firstvalue >= secondvalue)
        {
            add(listForMerging, secondvalue);
            secondPartPosition = next(secondPartPosition);
        }
        else
        {
            add(listForMerging, firstvalue);
            firstPartPosition = next(firstPartPosition);
        }
        indexOfFirstPartPosition = indexFromPosition(baseList, firstPartPosition);
        indexOfSecondPartPosition = indexFromPosition(baseList, secondPartPosition);
    }
    if (indexOfFirstPartPosition == listBorder - 1 && indexOfSecondPartPosition == stopIndex)
    {
        int const firstvalue = getValue(baseList, firstPartPosition);
        int const secondvalue = getValue(baseList, secondPartPosition);
        if (firstvalue >= secondvalue)
        {
            add(listForMerging, secondvalue);
            add(listForMerging, firstvalue);
        }
        else
        {
            add(listForMerging, firstvalue);
            add(listForMerging, secondvalue);
        }
    }
    else if (indexOfFirstPartPosition == listBorder - 1)
    {
        helpForMerge(baseList, listForMerging, firstPartPosition, secondPartPosition, stopIndex);
    }
    else if (indexOfSecondPartPosition == stopIndex)
    {
        helpForMerge(baseList, listForMerging, secondPartPosition, firstPartPosition, listBorder - 1);
    }
    return listForMerging;
}

void mergeSort(List* list, List* listForMerging, int startIndex, int stopIndex, List* baseList)
{
    int const size = sizeOfList(list);
    if (size > 1)
    {
        List* firstHalfOfList = createList();
        List* secondHalfOfList = createList();
        Position* i = first(list);
        int j = startIndex;
        int const difference = (stopIndex - startIndex);
        while (j <= startIndex + difference / 2)
        {
            add(firstHalfOfList, getValue(list, i));
            i = next(i);
            ++j;
        }
        int const listBorder = j;
        while (j <= startIndex + difference)
        {
            add(secondHalfOfList, getValue(list, i));
            i = next(i);
            ++j;
        }
        mergeSort(firstHalfOfList, listForMerging, startIndex, listBorder - 1, baseList);
        mergeSort(secondHalfOfList, listForMerging, listBorder, stopIndex, baseList);
        List* sortedList = merge(baseList, startIndex, listBorder, stopIndex);
        Position* k = getPositionFromIndex(baseList, startIndex);
        Position* positionOfSortedList = first(sortedList);
        int counterForRemove = 0;
        if (startIndex == 0)
        {
            addInHead(baseList, getValue(sortedList, positionOfSortedList));
            positionOfSortedList = next(positionOfSortedList);
            ++counterForRemove;
        }
        while (!last(positionOfSortedList))
        {
            addByPosition(baseList, k, getValue(sortedList, positionOfSortedList));
            positionOfSortedList = next(positionOfSortedList);
            k = next(k);
            ++counterForRemove;
        }
        //k = next(k);
        addByPosition(baseList, k, getValue(sortedList, positionOfSortedList));
        for (int j = 0; j < counterForRemove + 1; ++j)
        {
            deleteElementByPosition(baseList, k);
        }
        deleteList(sortedList);
    }
    else if (size <= 1)
    {
        return;
    }
}

int main()
{
    List* newList = createList();
    List* listForMerging = createList();
    addByPosition(newList, first(newList), 3);
    addByPosition(newList, first(newList), 8);
    addByPosition(newList, first(newList), 4);
    addByPosition(newList, first(newList), 1);
    Position* i = first(newList);
    while (!last(i))
    {
        i = next(i);
    }
    mergeSort(newList, listForMerging, 0, /*indexFromPosition(newList, i)*/ sizeOfList(newList) - 1, newList);
    for (Position* i = first(newList); !last(i); i = next(i))
    {
        printf("%d ", getValue(newList, i));
    }
}
