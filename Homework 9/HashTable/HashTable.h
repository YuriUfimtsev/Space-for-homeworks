#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef struct HashTable HashTable;

// ������� ������� ���-�������.
// ��������� ��������� �� ���-�������.
void deleteHashTable(HashTable* table);

// ������� ������� ���-������� � ��������� �� ���������� �� �����.
// ��������� ��������� �� ���������� ���� FILE.
// ���������� ��������� �� ���-�������.
HashTable* fillInHashTableFromFile(FILE* data);

// ������� ���������� ������� ����� ������ � ������ ���-�������.
float getAverageLengthOfListFromHashTable(HashTable* table);

// ������� ���������� ������������ ����� ������ � ������ ���-�������.
int getMaxLengthOfListFromHashTable(HashTable* table);

// ������� ���������� ����������� ���������� ������ ���-�������.
float getLoadFactorOfHashTable(HashTable* table);

// ������� ������� �� ����� ��� �����, ������� � ���-�������, ������ � ���������� numberOfRepetitions.
void printWordsWithNumbersOfRepetitions(HashTable* table);

// ������� ���������� �������� ��������� numberOfRepetitions ��� ������� ��������.
// ��������� �������� �������� ���-������� � ��������� �� ���� ���-�������.
int getNumberOfRepetitons(const char* data, HashTable* table);

// ������� ���������� ����� ���������, ������� � ���-�������.
int getNumberOfElements(HashTable* table);
