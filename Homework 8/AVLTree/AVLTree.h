#pragma once

#define valueAndKeySize 30

#include <stdbool.h>

// ��������� ������ �������
typedef struct Node Node;

// ������� ������� ������ �������.
Node* createEmptyDictionary();

// ������� ������� ������� � ���������: ���� key � �������� value.
// �������� ���������� �������(value) ������� �� ���������.
Node* createDictionary(const char* key, const char* value);

// ������� ������� �������
// ��������� ��������� �� �������.
void deleteDictionary(Node* dictionary);

// ������� ���������� �������� �������� � ������ key, �������� � �������.
// ������� ��������� ��������� �� �������, ���� key � bool ���������� ��� �������� ������������� ����� � �������.
// ��������� NULL, ���� ������� � ������ ������ � ������� �� ������.
const char* getValueFromDictionary(Node* dictionary, const char* key, bool* isKeyInDictionary);

// ������� ��������� ������� � �������. ��������� ����� ��������� �� �������,
// ���� key, �������� value, ������� ���������� ��������.
// �������� ���������� �������(value) ������� �� ���������.
void insertToDictionary(Node** dictionary, const char* key, const char* value);

// ������� ���������, ���� �� � ������� ������� � ������ key.
// ��������� ��������� �� �������, ���� key.
// ���������� true, ���� ������� ������, false �����.
bool isKeyInDictionary(Node* currentNode, const char* key);

// ������� ������� �� ������� ������� � ������ key.
// ��������� ��������� �� �������, ���� key.
void removeFromDictionary(Node* dictionary, const char* key);

// ������� ���������� ���� ������� �������� �������.
const char* getKeyFromDictionary(Node* dictionaryValue);

// ������� ���������� ��������� �� ������� ���� ������� ����.
Node* getRightChild(Node* currentNode);

// ������� ���������� ��������� �� ������ ���� ������� ����.
Node* getLeftChild(Node* currentNode);

// ������� ���������� �������� ������� ������� �������� �������.
char getBalanceFromAVLTree(Node* currentNode);

// ������� ���������, �������� �� ������ � ������ ����.
bool checkBalance(Node* currentNode);

// ������� ���������� ������ �������.
// � ���������, �������� �� ��������� ��������� ������ � �������.
int returnSize(Node* currentNode, int* size);
