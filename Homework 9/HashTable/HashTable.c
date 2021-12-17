#pragma warning(disable: 4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "List.h"
#include "HashTable.h"

typedef struct HashTable
{
    int numberForHashFunction;
    int countOfElements;
    int countOfBuckets;
    List** array;
} HashTable;

char* dataToInsert(const char* data)
{
    char* dataForHashTable = malloc(30);
    if (dataForHashTable == NULL)
    {
        return NULL;
    }
    strcpy_s(dataForHashTable, 30, data);
    return dataForHashTable;
}

int calculateHashFunction(const char* word, const int moduleForHash, int numberForHashFunction)
{
    int result = 0;
    unsigned int wordLength = (unsigned int)strlen(word);
    int numberForHashFunctionInDegree = 1;
    for (unsigned int i = 0; i < wordLength; ++i)
    {
        result += word[i] * numberForHashFunctionInDegree;
        numberForHashFunctionInDegree *= numberForHashFunction;
    }
    result = abs(result);
    return result % moduleForHash;
}

bool increaseHashTable(HashTable* table)
{
    const int currentSizeOfArray = table->countOfBuckets;
    const int newSize = currentSizeOfArray * 2;
    List** newArray = calloc(newSize, sizeof(List*));
    if (newArray == NULL)
    {
        return false;
    }
    for (int i = 0; i < newSize; ++i)
    {
        List* newList = createList();
        newArray[i] = newList;
    }
    for (int i = 0; i < currentSizeOfArray; ++i)
    {
        if (getNumberOfListElements(table->array[i]) > 0)
        {
            for (Position* j = first(table->array[i]); !last(j); next(j))
            {
                const int numberOfRepetitions = getNumberOfRepetitionsByPosition(j);
                const char* data = dataToInsert(getData(j));
                const int hashFinction = calculateHashFunction(data, newSize, table->numberForHashFunction);
                addTheDataInList(newArray[hashFinction], numberOfRepetitions, data);
            }
        }
        deleteList(table->array[i]);
    }
    free(table->array);
    table->array = newArray;
    table->countOfBuckets = newSize;
    return true;
}

HashTable* createHashTable(int numberForHashFunction)
{
    HashTable* newTable = calloc(1, sizeof(HashTable));
    if (newTable == NULL)
    {
        return NULL;
    }
    newTable->numberForHashFunction = numberForHashFunction;
    List** array = calloc(numberForHashFunction, sizeof(List*));
    if (array == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < numberForHashFunction; ++i)
    {
        List* newList = createList();
        array[i] = newList;
    }
    newTable->array = array;
    newTable->countOfBuckets = numberForHashFunction;
    return newTable;
}

void insertToHashTable(const char* data, HashTable* table)
{
    const char* requiredData = dataToInsert(data);
    const int key = calculateHashFunction(requiredData, table->countOfBuckets, table->numberForHashFunction);
    if (addTheDataInList(table->array[key], 1, requiredData))
    {
        ++table->countOfElements;
    }
    double loadFactor = table->countOfElements / table->countOfBuckets;
    if (loadFactor >= 0.85)
    {
        increaseHashTable(table);
    }
}

void removeElementFromHashTable(const char* data, HashTable* table)
{
    const int key = calculateHashFunction(data, table->countOfBuckets, table->numberForHashFunction);
    if (delete(table->array[key], data))
    {
        --table->countOfElements;
    }
}

void deleteHashTable(HashTable* table)
{
    const int sizeOfHashTable = table->countOfBuckets;
    for (int i = 0; i < sizeOfHashTable; ++i)
    {
        deleteList(table->array[i]);
    }
    free(table->array);
    free((void*)table);
}

int getNumberOfElements(HashTable* table)
{
    return table->countOfElements;
}

int getNumberOfRepetitons(const char* data, HashTable* table)
{
    const int key = calculateHashFunction(data, table->countOfBuckets, table->numberForHashFunction);
    return getNumberOfRepetitionsByHash(data, table->array[key]);
}

void printWordsWithNumbersOfRepetitions(HashTable* table)
{
    for (int i = 0; i < table->countOfBuckets; ++i)
    {
        if (getNumberOfListElements(table->array[i]) != 0)
        {
            for (Position* j = first(table->array[i]); !last(j); next(j))
            {
                printf("The word '%s' occurs %d times.\n", getData(j), getNumberOfRepetitionsByPosition(j));
            }
        }
    }
}

float getLoadFactorOfHashTable(HashTable* table)
{
    float result = (float) table->countOfElements / table->countOfBuckets;
    return result;
}

int getMaxLengthOfListFromHashTable(HashTable* table)
{
    int maxLength = 0;
    for (int i = 0; i < table->countOfBuckets; ++i)
    {
        int currentListLength = getNumberOfListElements(table->array[i]);
        if (currentListLength > maxLength)
        {
            maxLength = currentListLength;
        }
    }
    return maxLength;
}

float getAverageLengthOfListFromHashTable(HashTable* table)
{
    int numberOfLists = 0;
    int commonListsLength = 0;
    for (int i = 0; i < table->countOfBuckets; ++i)
    {
        int currentListLength = getNumberOfListElements(table->array[i]);
        if (currentListLength > 0)
        {
            ++numberOfLists;
            commonListsLength += currentListLength;
        }
    }
    float result = (float) commonListsLength / numberOfLists;
    return result;
}

HashTable* fillInHashTableFromFile(FILE* data)
{
    HashTable* table = createHashTable(113);
    char word[30] = { '\0' };
    while (fscanf(data, "%s", &word) > 0)
    { 
        insertToHashTable(word, table);
    }
    return table;
}