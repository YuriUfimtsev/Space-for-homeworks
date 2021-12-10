#pragma once

#include <stdbool.h>

typedef struct Node Node;

// ������� ������� ������ - ������, ��� ������ ����. ���������� ��������� �� ������ ����.
Node* createEmptyNode();

// ������� ������� ��� ������. ������� ������, ���������� ��� ����.
// ��������� ��������� �� ������ ������.
void deleteTree(Node* parent);

// ������� ��������� ����� ���� � ������ key � ��������� value � ������ tree.
// ��������� ��������� �� ������ ������, ���� key � ��������� �� ������ value.
void insertToTree(Node* currentNode, const int key, const char* value);

// ������� ���������, ���� �� � ������ tree ������� � ������ key.
// ��������� ��������� �� ������ ������, ���� key.
// ���������� true, ���� ������� ������ � false - ���� �� ������.
bool isKeyInTree(Node* currentNode, const int key);

// ������� ���������� �������� �������� � ������ key, �������� � ������ tree.
// ������� ��������� ��������� �� ������ ������ tree � ���� key.
// ��������� NULL, ���� ������� � ������ ������ � ������ �� ������.
// ���� �� ������� ������, ������� ������ �������� �������� - ��������� �� ������ value.
const char* findInTree(Node* currentNode, const int key);

// ������� ������� �� ������ tree ������� � ������ key. 
// ��������� ��������� �� ���� ������ tree, ��������� �� ������ ������ root � ���� key.
void removeFromTree(Node* currentNode, Node* parent, const int key);

const char* getValueFromTree(Node* currentNode);

const int getKeyFromTree(Node* currentNode);

Node* getRightChild(Node* currentNode);

Node* getLeftChild(Node* currentNode);

Node* createNode(const int key, const char* value);
