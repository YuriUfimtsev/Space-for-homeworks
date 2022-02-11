#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "List.h"
#include "TestsForMergeSort.h"

const char* returnCorrectValue(List* list, Position* position, enum Key key)
{
    return key == name ? getData(list, position).name : getData(list, position).phone;
}

List* readEntriesFromFile(FILE* data)
{
    List* listOfEntries = createList();
    int i = 0;
    fseek(data, 0, SEEK_END);
    int position = ftell(data);
    char name[15] = { '\0' };
    char phone[15] = { '\0' };
    if (position != 0)
    {
        fseek(data, 0, SEEK_SET);
        while (!feof(data))
        {
            int const checkOfEof = fscanf(data, "%s", name);
            if (checkOfEof == EOF)
            {
                break;
            }
            fscanf(data, "%s", phone);
            ++i;
            add(listOfEntries, name, phone);
        }
    }
    return listOfEntries;
}

List* merge(List* firstHalfOfList, List* secondHalfOfList, enum Key key)
{
    List* listForMerging = createList();
    int sizeOfListForMerging = 0;
    Position* secondPartPosition = first(secondHalfOfList);
    char secondHalfOfListName[15] = { '\0' };
    strcpy(secondHalfOfListName, getData(secondHalfOfList, secondPartPosition).name);
    char secondHalfOfListPhone[15] = { '\0' };
    strcpy(secondHalfOfListPhone, getData(secondHalfOfList, secondPartPosition).phone);
    char firstHalfOfListName[15] = { '\0' };
    char firstHalfOfListPhone[15] = { '\0' };
    char secondHalfOfListValue[15] = { '\0' };
    char firstHalfOfListValue[15] = { '\0' };
    strcpy(secondHalfOfListValue, returnCorrectValue(secondHalfOfList, secondPartPosition, key));
    Position* startedPosition = first(firstHalfOfList);
    for (Position* i = startedPosition; !last(i); next(i))
    {
        strcpy(firstHalfOfListName, getData(firstHalfOfList, i).name);
        strcpy(firstHalfOfListPhone, getData(firstHalfOfList, i).phone);
        strcpy(firstHalfOfListValue, returnCorrectValue(firstHalfOfList, i, key));
        int resultOfComparison = strcmp(firstHalfOfListValue, secondHalfOfListValue);
        while (resultOfComparison >= 0 && !last(secondPartPosition))
        {
            add(listForMerging, secondHalfOfListName, secondHalfOfListPhone);
            next(secondPartPosition);
            if (!last(secondPartPosition))
            {
                strcpy(secondHalfOfListValue, returnCorrectValue(secondHalfOfList, secondPartPosition, key));
                strcpy(secondHalfOfListName, getData(secondHalfOfList, secondPartPosition).name);
                strcpy(secondHalfOfListPhone, getData(secondHalfOfList, secondPartPosition).phone);
                resultOfComparison = strcmp(firstHalfOfListValue, secondHalfOfListValue);
            }
        }
        add(listForMerging, firstHalfOfListName, firstHalfOfListPhone);
    }
    deletePosition(startedPosition);
    while (!last(secondPartPosition))
    {
        strcpy(secondHalfOfListName, getData(secondHalfOfList, secondPartPosition).name);
        strcpy(secondHalfOfListPhone, getData(secondHalfOfList, secondPartPosition).phone);
        add(listForMerging, secondHalfOfListName, secondHalfOfListPhone);
        next(secondPartPosition);
    }
    deletePosition(secondPartPosition);
    return listForMerging;
}

List* mergeSort(List* listForSorting, enum Key key)
{
    int const size = getSizeOfList(listForSorting);
    if (size <= 1)
    {
        return listForSorting;
    }
    List* firstHalfOfList = createList();
    List* secondHalfOfList = createList();
    int sizeOfFirstHalfOfList = 0;
    int sizeOfSecondHalfOfList = 0;
    Position* i = first(listForSorting);
    int j = 0;
    while (j < size / 2)
    {
        add(firstHalfOfList, getData(listForSorting, i).name,
            getData(listForSorting, i).phone);
        next(i);
        ++j;
    }
    while (j < size)
    {
        add(secondHalfOfList, getData(listForSorting, i).name,
            getData(listForSorting, i).phone);
        next(i);
        ++j;
    }
    List* sortedFirstHalfOfList = mergeSort(firstHalfOfList, key);
    List* sortedSecondHalfOfList = mergeSort(secondHalfOfList, key);
    deleteList(listForSorting);
    List* sortedList = merge(sortedFirstHalfOfList, sortedSecondHalfOfList, key);
    deletePosition(i);
    deleteList(sortedFirstHalfOfList);
    deleteList(sortedSecondHalfOfList);
    return sortedList;
}
