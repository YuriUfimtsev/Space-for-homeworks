#pragma warning(disable: 4996)

#include "TestsForHashTable.h"

#include "HashTable.h"

#include <stdio.h>

bool isHashTableCorrect()
{
    FILE* data = fopen("testData.txt", "r");
    HashTable* table = fillInHashTableFromFile(data);
    bool const result = getNumberOfElements(table) == 25 && getNumberOfRepetitons("��������.", table) == 2
        && getNumberOfRepetitons("�������", table) == 2 && getNumberOfRepetitons("��������", table) == 1
        && getNumberOfRepetitons("�����", table) == 0;
    deleteHashTable(table);
    return result;
}