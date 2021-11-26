#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../MergeSort/List.h"

const char* returnCorrectValue(List* list, Position* position, int const key)
{
    if (key == 1)
    {
        return getData(list, position).name;
    }
    if (key == 2)
    {
        return getData(list, position).phone;
    }
}

List* readEntriesFromFile(FILE* data, int* sizeOfList)
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
            add(listOfEntries, name, phone, sizeOfList);
        }
    }
    return listOfEntries;
}

List* merge(List* firstHalfOfList, List* secondHalfOfList, const int key)
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
            add(listForMerging, secondHalfOfListName, secondHalfOfListPhone, &sizeOfListForMerging);
            next(secondPartPosition);
            if (!last(secondPartPosition))
            {
                strcpy(secondHalfOfListValue, returnCorrectValue(secondHalfOfList, secondPartPosition, key));
                strcpy(secondHalfOfListName, getData(secondHalfOfList, secondPartPosition).name);
                strcpy(secondHalfOfListPhone, getData(secondHalfOfList, secondPartPosition).phone);
                resultOfComparison = strcmp(firstHalfOfListValue, secondHalfOfListValue);
            }
        }
        add(listForMerging, firstHalfOfListName, firstHalfOfListPhone, &sizeOfListForMerging);
    }
    deletePosition(startedPosition);
    while (!last(secondPartPosition))
    {
        strcpy(secondHalfOfListName, getData(secondHalfOfList, secondPartPosition).name);
        strcpy(secondHalfOfListPhone, getData(secondHalfOfList, secondPartPosition).phone);
        add(listForMerging, secondHalfOfListName, secondHalfOfListPhone, &sizeOfListForMerging);
        next(secondPartPosition);
    }
    deletePosition(secondPartPosition);
    return listForMerging;
}

List* mergeSort(List* listForSorting, const int key, int* sizeOfList)
{
    int const size = *sizeOfList;
    if (size > 1)
    {
        List* firstHalfOfList = createList();
        List* secondHalfOfList = createList();
        int sizeOfFirstHalfOfList = 0;
        int sizeOfSecondHalfOfList = 0;
        Position* i = first(listForSorting);
        int j = 0;
        while (j < size / 2)
        {
            add(firstHalfOfList, getData(listForSorting, i).name,
                getData(listForSorting, i).phone, &sizeOfFirstHalfOfList);
            next(i);
            ++j;
        }
        while (j < size)
        {
            add(secondHalfOfList, getData(listForSorting, i).name,
                getData(listForSorting, i).phone, &sizeOfSecondHalfOfList);
            next(i);
            ++j;
        }
        List* sortedFirstHalfOfList = mergeSort(firstHalfOfList, key, &sizeOfFirstHalfOfList);
        List* sortedSecondHalfOfList = mergeSort(secondHalfOfList, key, &sizeOfSecondHalfOfList);
        List* sortedList = merge(sortedFirstHalfOfList, sortedSecondHalfOfList, key);
        deletePosition(i);
        deleteList(firstHalfOfList);
        deleteList(secondHalfOfList);
        return sortedList;
    }
    return listForSorting;
}

bool testOfMergeSortingByName()
{
    FILE* data = fopen("Test.txt", "r");
    if (data == NULL)
    {
        return false;
    }
    int sizeOfList = 0;
    List* listOfEntries = readEntriesFromFile(data, &sizeOfList);
    fclose(data);
    List* sortedListWith1 = mergeSort(listOfEntries, 1, &sizeOfList);
    char nameForCheck[15] = {'\0'};
    char phoneForCheck[15] = {'\0'};
    FILE* result = fopen("ExpectedResultOfTest1.txt", "r");
    if (result == NULL)
    {
        deleteList(listOfEntries);
        deleteList(sortedListWith1);
        return false;
    }
    Position* startedPosition = first(sortedListWith1);
    for (Position* i = startedPosition; !last(i); next(i))
    {
        fscanf(result, "%s", nameForCheck);
        fscanf(result, "%s", phoneForCheck);
        if (strcmp(getData(sortedListWith1, i).name, nameForCheck) != 0 ||
            strcmp(getData(sortedListWith1, i).phone, phoneForCheck) != 0)
        {
            deletePosition(i);
            deleteList(listOfEntries);
            deleteList(sortedListWith1);
            fclose(result);
            return false;
        }
    }
    deletePosition(startedPosition);
    fclose(result);
    deleteList(listOfEntries);
    deleteList(sortedListWith1);
    return true;
}

int main()
{
    if (!testOfMergeSortingByName())
    {
        printf("Tests failed");
        return -1;
    }
    FILE* data = fopen("Data.txt", "r");
    if (data == NULL)
    {
        printf("File not found");
        return -1;
    }
    printf("How do you want sorting the notes?\n");
    printf("Enter 1 if you want sorting by name.\nEnter 2 if you want sorting by phone number\n");
    printf("Your choice: ");
    int key = 0;
    scanf("%d", &key);
    if (key != 1 && key != 2)
    {
        printf("\nIncorrect value\n");
        fclose(data);
        return -1;
    }
    int sizeOfList = 0;
    List* listOfEntries = readEntriesFromFile(data, &sizeOfList);
    fclose(data);
    List* sortedList = mergeSort(listOfEntries, key, &sizeOfList);
    printf("\nResult of sorting: \n");
    Position* startedPosition = first(sortedList);
    for (Position* i = startedPosition; !last(i); next(i))
    {
        printf("%s %s \n", getData(sortedList, i).name, getData(sortedList, i).phone);
    }
    deletePosition(startedPosition);
    deleteList(listOfEntries);
    deleteList(sortedList);
}
