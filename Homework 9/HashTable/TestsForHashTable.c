#pragma warning(disable: 4996)

#include "TestsForHashTable.h"

#include "HashTable.h"

#include <stdio.h>

bool isHashTableCorrect()
{
    FILE* data = fopen("testData.txt", "r");
    HashTable* table = fillInHashTableFromFile(data);
    bool const result = getNumberOfElements(table) == 25 && getNumberOfRepetitons("структур.", table) == 2
        && getNumberOfRepetitons("методов", table) == 2 && getNumberOfRepetitons("описание", table) == 1
        && getNumberOfRepetitons("книга", table) == 0;
    deleteHashTable(table);
    return result;
}