#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef struct HashTable HashTable;

// Функция удаляет хеш-таблицу.
// Принимает указатель на хеш-таблицу.
void deleteHashTable(HashTable* table);

// Функция создает хеш-таблицу и заполняет ее элементами из файла.
// Принимает указатель на переменную типа FILE.
// Возвращает указатель на хеш-таблицу.
HashTable* fillInHashTableFromFile(FILE* data);

// Функция возвращает среднюю длину списка в данной хеш-таблице.
float getAverageLengthOfListFromHashTable(HashTable* table);

// Функция возвращает максимальную длину списка в данной хеш-таблице.
int getMaxLengthOfListFromHashTable(HashTable* table);

// Функция возвращает коэффициент заполнения данной хеш-таблицы.
float getLoadFactorOfHashTable(HashTable* table);

// Функция выводит на экран все слова, лежащие в хэш-таблице, вместе с параметром numberOfRepetitions.
void printWordsWithNumbersOfRepetitions(HashTable* table);

// Функция возвращает значение параметра numberOfRepetitions для данного элемента.
// Принимает значение элемента хэш-таблицы и указатель на саму хеш-таблицу.
int getNumberOfRepetitons(const char* data, HashTable* table);

// Функция возвращает число элементов, лежащих в хеш-таблице.
int getNumberOfElements(HashTable* table);
