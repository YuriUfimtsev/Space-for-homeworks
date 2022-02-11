#pragma warning(disable: 4996)

#define NUMBER_FOR_HASH_FUNCTION 113

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "List.h"
#include "HashTable.h"

typedef struct HashTable
{
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

int calculateHashFunction(const char* word, const int moduleForHash)
{
    int result = 0;
    unsigned int wordLength = (unsigned int)strlen(word);
    int numberForHashFunctionInDegree = 1;
    for (unsigned int i = 0; i < wordLength; ++i)
    {
        result += word[i] * numberForHashFunctionInDegree;
        numberForHashFunctionInDegree *= NUMBER_FOR_HASH_FUNCTION;
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
        if (newList == NULL)
        {
            for (int j = 0; j < i; ++j)
            {
                free(newArray[j]);
                free(newArray);
            }
            return false;
        }
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
                const int hashFunction = calculateHashFunction(data, newSize);
                addTheDataInList(newArray[hashFunction], numberOfRepetitions, data);
            }
        }
        deleteList(table->array[i]);
    }
    free(table->array);
    table->array = newArray;
    table->countOfBuckets = newSize;
    return true;
}

HashTable* createHashTable()
{
    HashTable* newTable = calloc(1, sizeof(HashTable));
    if (newTable == NULL)
    {
        return NULL;
    }
    List** array = calloc(NUMBER_FOR_HASH_FUNCTION, sizeof(List*));
    if (array == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < NUMBER_FOR_HASH_FUNCTION; ++i)
    {
        List* newList = createList();
        array[i] = newList;
    }
    newTable->array = array;
    newTable->countOfBuckets = NUMBER_FOR_HASH_FUNCTION;
    return newTable;
}

void insertToHashTable(const char* data, HashTable* table)
{
    const char* requiredData = dataToInsert(data);
    const int key = calculateHashFunction(requiredData, table->countOfBuckets);
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
    const int key = calculateHashFunction(data, table->countOfBuckets);
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
    const int key = calculateHashFunction(data, table->countOfBuckets);
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
    return (float)table->countOfElements / table->countOfBuckets;;
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