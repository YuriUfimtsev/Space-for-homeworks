#include "TestsForMergeSort.h"
#include "List.h"
#include "MergeSort.h"

#include <stdio.h>

bool testOfMergeSortingByName()
{
    FILE* data = fopen("Test.txt", "r");
    if (data == NULL)
    {
        return false;
    }
    int sizeOfList = 0;
    List* listOfEntries = readEntriesFromFile(data);
    fclose(data);
    List* sortedListWith1 = mergeSort(listOfEntries, name);
    char nameForCheck[15] = { '\0' };
    char phoneForCheck[15] = { '\0' };
    FILE* result = fopen("ExpectedResultOfTest1.txt", "r");
    if (result == NULL)
    {
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
            deleteList(sortedListWith1);
            fclose(result);
            return false;
        }
    }
    deletePosition(startedPosition);
    fclose(result);
    deleteList(sortedListWith1);
    return true;
}
