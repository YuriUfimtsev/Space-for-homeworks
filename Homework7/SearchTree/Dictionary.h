#pragma once

#define MAX_SIZE_OF_STRING 30

typedef struct Node Dictionary;

// ������� ������� �������. ���������� ��������� �� ������ ������� �������.
Dictionary* createDictionary();

//// ������� ��������� ������� � ������ key � ��������� value � �������.
// ��������� ��������� �� ������ ������� �������,
// ���� key � ��������� �� ������ value.
void addToDictionary(Dictionary* dictionary, const int key, const char* value);

// ������� ���������� �������� �������� � ������ key, �������� � �������.
// ������� ��������� ��������� �� ������ ������� ������� � ���� key.
// ��������� NULL, ���� ������� � ������ ������ � ������� �� ������.
// ���� �� ������� ������, ������� ������ �������� �������� - ��������� �� ������ value.
const char* getValueFromDictionary(Dictionary* dictionary, const int key, bool* keyInDictionary);

// ������� ���������, ���� �� � ������� ������� � ������ key.
// ��������� ��������� �� ������ ������� �������, ���� key.
// ���������� true, ���� ������� ������, false �����.
bool isKeyInDictionary(Dictionary* dictionary, const int key);

// ������� ������� �� ������� ������� � ������ key. 
// ��������� ��������� �� ������� ������� � ���� key.
void removeFromDictionary(Dictionary* dictionary, const int key);

// ������� ������� �������. ������� ������, ���������� ��� ����.
// ��������� ��������� �� ������ ������� �������.
void deleteDictionary(Dictionary* dictionary);
