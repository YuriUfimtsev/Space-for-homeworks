#pragma once

#include <stdbool.h>

typedef struct Node {
    int key;
    char* value;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

// ������� ������� ������ - ������, ��� ������ ����. ���������� ��������� �� ������ ����.
Node* createNode();

// ������� ������� ������, ���������� �� ������ ����. ��������� ��������� �� ����.
void deleteNode(Node* node);

// ������� ������� ��� ������. ������� ������, ���������� ��� ����.
// ��������� ��������� �� ������ ������.
void deleteTree(Node* root);

// ������� ��������� ����� ���� � ������ key � ��������� value � ������ tree.
// ��������� ��������� �� ������ ������, ���� key � ��������� �� ������ value.
void insertToTree(Node* tree, const int key, char* value);

// ������� ���������, ���� �� � ������ tree ������� � ������ key.
// ��������� ��������� �� ������ ������, ���� key.
// ���������� true, ���� ������� ������ � false - ���� �� ������.
bool isKeyInTree(Node* tree, const int key);

// ������� ���������� �������� �������� � ������ key, �������� � ������ tree.
// ������� ��������� ��������� �� ������ ������ tree � ���� key.
// ��������� NULL, ���� ������� � ������ ������ � ������ �� ������.
// ���� �� ������� ������, ������� ������ �������� �������� - ��������� �� ������ value.
char* findInTree(Node* tree, const int key);

// ������� ������� �� ������ tree ������� � ������ key. 
// ��������� ��������� �� ���� ������ tree, ��������� �� ������ ������ root � ���� key.
void removeFromTree(Node* tree, Node* root, const int key);
