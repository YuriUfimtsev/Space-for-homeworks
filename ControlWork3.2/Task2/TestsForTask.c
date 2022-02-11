#pragma warning (disable: 4996)

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "TestsForTask.h"
#include "List.h"

bool standartTest()
{
    FILE* data = fopen("DataForStandartTest.txt", "r");
    List* newList = fillListFromFile(data);
    if (newList == NULL)
    {
        return false;
    }
    Position* i = first(newList);
    const bool firstPartOfResult = strcmp(getValue(newList, i), "abcdef") == 0;
    next(i);
    const bool secondPartOfResult = (getValue(newList, i) == NULL);
    free(i);
    deleteList(newList);
    return firstPartOfResult && secondPartOfResult;
}

bool testWithEmptyFile()
{
    FILE* data = fopen("EmptyDataForTest.txt", "r");
    List* newList = fillListFromFile(data);
    if (newList == NULL)
    {
        return false;
    }
    Position* i = first(newList);
    const bool result = getValue(newList, i) == NULL;
    free(i);
    deleteList(newList);
    return result;
}

bool areTestsPassing()
{
    return standartTest() && testWithEmptyFile();
}