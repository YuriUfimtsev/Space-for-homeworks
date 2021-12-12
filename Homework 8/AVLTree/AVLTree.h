#pragma once

#include <stdbool.h>

typedef struct Node Node;

// ������� ������� ������ ������. ���������� ��������� �� ������ ����.
Node* createEmptyNode();

// ������� ������� ������ � ������ key � ��������� value � �����.
Node* createNode(const int key, const char* value);

// ������� ������� ��� ������.
// ��������� ��������� �� ������ ������.
void deleteAVLTree(Node* parent);

// ������� ���������� �������� �������� � ������ key, �������� � ������ tree.
// ������� ��������� ��������� �� ������ ������ root � ���� key.
// ��������� NULL, ���� ������� � ������ ������ � ������ �� ������.
const char* advancedGetValue(Node* root, const int key);

// ������� ��������� ������� � ��� ������. ��������� ����� ��������� �� ������ ������,
// ���� key, �������� value, ������� ���������� ��������
void advancedInsertToAVLTree(Node** root, const int key, const char* value);

// ������� ���������, ���� �� � ������ tree ������� � ������ key.
// ��������� ��������� �� ������ ������, ���� key.
// ���������� true, ���� ������� ������, false �����.
bool isKeyInAVLTree(Node* currentNode, const int key);

// ������� ������� �� ������ ������� � ������ key.
// ��������� ��������� �� ������ ������ root, ���� key.
void advancedRemoveFromAVLTree(Node* root, const int key);

// ������� ��������� ��������� �� ������ ������ � ����.
// ��������� ��������, ��������������� ����� �����.
const char* getValueFromAVLTree(Node* currentNode, const int key);

// ������� ���������� ���� ������� ����.
const int getKeyFromAVLTree(Node* currentNode);

// ������� ���������� ��������� �� ������� ���� ������� ����.
Node* getRightChild(Node* currentNode);

// ������� ���������� ��������� �� ������ ���� ������� ����.
Node* getLeftChild(Node* currentNode);

// ������� ���������� �������� ������� ������� ����.
char getBalanceFromAVLTree(Node* currentNode);
