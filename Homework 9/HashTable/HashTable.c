#define numberForHashFunction 113

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "List.h"

typedef struct HashTable
{
    int countOfElements;
    int countOfBuckets;
    List* array[];
} HashTable;

bool isSimple(const int number) // не нужна в итоге:(:(:(
{
    int squareRoot = (int)sqrt(number);
    bool isSimple = true;
    for (int i = 2; i < squareRoot + 1; ++i)
    {
        if (number % i == 0)
        {
            isSimple = false;
            break;
        }
    }
    return isSimple;
}

int findTheMoreSimpleNumber(int currentSimpleNumber) // не нужна в итоге:(:(:(
{
    int result = 0;
    while (result == 0)
    {
        if (isSimple(currentSimpleNumber))
        {
            result = currentSimpleNumber;
        }
        currentSimpleNumber += 2;
    }
    return result;
}

int calculateHashFunction(const char* word, const int moduleForHash)
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

List* increaseHashTable(HashTable* table)
{
    const int currentSizeOfArray = table->countOfBuckets;
    const int newSize = currentSizeOfArray * 2;
    List* newArray = calloc(newSize, sizeof(List*));
    for (int i = 0; i < currentSizeOfArray; ++i)
    {
        if (getNumberOfListElements(table->array[i]) > 0)
        {
            for (Position* j = first(table->array[i]); !last(j); next(j))
            {
                const int numbersOrRepetition = getNumberOfRepetitions(table->array[i]);
                const char* data = getData(table->array[i]);
                const int hashFinction = calculateHashFunction(data, newSize);
                addTheValueInSortedList(newArray, data);///// - изменить в функцию:
                // обычное добавление в конец с проверкой на повтор. И в качестве еще одного параметра - хэш
                // (т.е. индекс)
            }
            deleteList(table->array[i]);
        }
    }
}

void insertToHashTable(const char* word)
{
    const int key = calculateHashFunction(word);

}

void removeFromHashTable(const char* word)
{

}

const char* findInHashTable()
{

}