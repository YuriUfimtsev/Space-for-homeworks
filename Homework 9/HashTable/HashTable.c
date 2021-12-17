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

//bool isSimple(const int number) // не нужна в итоге:(:(:(
//{
//    int squareRoot = (int)sqrt(number);
//    bool isSimple = true;
//    for (int i = 2; i < squareRoot + 1; ++i)
//    {
//        if (number % i == 0)
//        {
//            isSimple = false;
//            break;
//        }
//    }
//    return isSimple;
//}
//
//int findTheMoreSimpleNumber(int currentSimpleNumber) // не нужна в итоге:(:(:(
//{
//    int result = 0;
//    while (result == 0)
//    {
//        if (isSimple(currentSimpleNumber))
//        {
//            result = currentSimpleNumber;
//        }
//        currentSimpleNumber += 2;
//    }
//    return result;
//}

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
    for (int i = 0; i < currentSizeOfArray; ++i)
    {
        if (getNumberOfListElements(table->array[i]) > 0)
        {
            for (Position* j = first(table->array[i]); !last(j); next(j))
            {
                const int numberOfRepetitions = getNumberOfRepetitions(j);
                const char* data = getData(j);
                const int hashFinction = calculateHashFunction(data, newSize, table->numberForHashFunction);
                addTheValueInList(newArray[hashFinction], numberOfRepetitions, data);
            }
            deleteList(table->array[i]);
        }
    }
    //deleteBackArray(table)
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
    const int key = calculateHashFunction(data, table->countOfBuckets, table->numberForHashFunction);
    if (addTheValueInList(table->array[key], 1, data))
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