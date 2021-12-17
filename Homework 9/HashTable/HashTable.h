#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef struct HashTable HashTable;

int calculateHashFunction(const char*, const int moduleForHash, int numberForHashFunction);

bool increaseHashTable(HashTable* table);

HashTable* createHashTable(int numberForHashFunction);

void insertToHashTable(char* data, HashTable* table);

void removeElementFromHashTable(const char* data, HashTable* table);

void deleteHashTable(HashTable* table);

HashTable* fillInHashTableFromFile(FILE* data);

float getAverageLengthOfListFromHashTable(HashTable* table);

int getMaxLengthOfListFromHashTable(HashTable* table);

float getLoadFactorOfHashTable(HashTable* table);

void printWordsWithNumbersOfRepetitions(HashTable* table);

int getNumberOfRepetitons(const char* data, HashTable* table);

int getNumberOfElements(HashTable* table);
