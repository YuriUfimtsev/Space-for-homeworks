#pragma warning(disable: 4996)

#include <stdio.h>
#include <locale.h>
#include <string.h>

#include "HashTable.h"
#include "TestsForHashTable.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");
    if (argc == 2 && strcmp(argv[1], "tests_only") == 0)
    {
        return isTestForHashTablePassing() ? 0 : -2;
    }
    if (!isTestForHashTablePassing())
    {
        printf("Tests failed");
        return -1;
    }
    FILE* data = fopen("Homework9/HashTable/Data.txt", "r");
    HashTable* table = fillInHashTableFromFile(data);
    fclose(data);
    printf("The load factor of hash table = %f.\n", getLoadFactorOfHashTable(table));
    printf("Max lentgth of list from hash table = %d.\n", getMaxLengthOfListFromHashTable(table));
    printf("Average length of list from hash table = %f.\n", getAverageLengthOfListFromHashTable(table));
    printf("\nIn this file\n");
    printWordsWithNumbersOfRepetitions(table);
    deleteHashTable(table);
}
