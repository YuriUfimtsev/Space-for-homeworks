#pragma warning(disable: 4996)

#include <stdio.h>
#include <locale.h>

#include "HashTable.h"
#include "TestsForHashTable.h"

int main()
{
    setlocale(LC_ALL, "Rus");
    if (!isTestForHashTablePassing())
    {
        printf("Tests failed");
        return -1;
    }
    FILE* data = fopen("Data.txt", "r");
    HashTable* table = fillInHashTableFromFile(data);
    printf("The load factor of hash table = %f.\n", getLoadFactorOfHashTable(table));
    printf("Max lentgth of list from hash table = %d.\n", getMaxLengthOfListFromHashTable(table));
    printf("Average length of list from hash table = %f.\n", getAverageLengthOfListFromHashTable(table));
    printf("\nIn this file\n");
    printWordsWithNumbersOfRepetitions(table);
    deleteHashTable(table);
}
