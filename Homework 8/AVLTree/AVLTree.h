#pragma once

#include <stdbool.h>

typedef struct Node Node;

// ������� ������� ������ ������. ���������� ��������� �� ������ ����.
Node* createEmptyNode();

// ������� ������� ������ � ������ key � ��������� value � �����.
Node* createNode(const int key, const char* value);

// ������� ������� ��� ������. ������� ������, ���������� ��� ����.
// ��������� ��������� �� ������ ������.
void deleteAVLTree(Node* parent);

// ������� ���������� �������� �������� � ������ key, �������� � ������ tree.
// ������� ��������� ��������� �� ������ ������ tree � ���� key.
// ��������� NULL, ���� ������� � ������ ������ � ������ �� ������.
// ���� �� ������� ������, ������� ������ �������� �������� - ��������� �� ������ value.
const char* advancedGetValue(Node* root, const int key);


void advancedInsertToAVLTree(Node** root, const int key, const char* value);

// ������� ���������, ���� �� � ������ tree ������� � ������ key.
// ��������� ��������� �� ������ ������, ���� key.
// ���������� true, ���� ������� ������, false �����.
bool isKeyInAVLTree(Node* currentNode, const int key);

// ������� ������� �� ������ tree ������� � ������ key.
// ��������� ��������� �� ������ ������ root
// � ��������� �� ������� ���� (���� ������ ������) currentNode, ���� key.
void advancedRemoveFromAVLTree(Node* root, const int key);

// ������� �� ������� �������� ���� ���������� ��������, ������� � ���.
const char* getValueFromAVLTree(Node* currentNode, const int key);


// ������� ���������� ���� ������� ����.
const int getKeyFromAVLTree(Node* currentNode);

// ������� ���������� ��������� �� ������� ���� ������� ����.
Node* getRightChild(Node* currentNode);

// ������� ���������� ��������� �� ������ ���� ������� ����.
Node* getLeftChild(Node* currentNode);

Node* insertToAVLTree(Node* currentNode, const int key, const char* value, Node* root,
    bool* areBalancesCorrect, bool* isBalance);

char getBalanceFromAVLTree(Node* currentNode);

