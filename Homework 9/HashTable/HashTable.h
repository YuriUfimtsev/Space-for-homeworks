#pragma once

#include <stdbool.h>

typedef struct HashTable HashTable;

int calculateHashFunction(const char*, const int moduleForHash, int numberForHashFunction);

bool increaseHashTable(HashTable* table);

HashTable* createHashTable(int numberForHashFunction);

void insertToHashTable(const char* data, HashTable* table);

void removeElementFromHashTable(const char* data, HashTable* table);

void deleteHashTable(HashTable* table);

