#pragma once

#include <stdbool.h>

typedef struct Node Node;

// Функция создает пустое дерево. Возвращает указатель на данный узел.
Node* createEmptyNode();

// Функция создает дерево с ключем key и значением value в корне.
Node* createNode(const int key, const char* value);

// Функция удаляет все дерево. Очищает память, выделенную под него.
// Принимает указатель на корень дерева.
void deleteTree(Node* parent);

// Функция добавляет новый узел с ключом key и значением value в дерево tree.
// Принимает указатель на корень дерева, ключ key и указатель на строку value.
Node* insertToTree(Node* currentNode, const int key, const char* value);

// Функция проверяет, есть ли в дереве tree элемент с ключом key.
// Принимает указатель на корень дерева, ключ key.
// Возвращает true, если элемент найден, false иначе.
bool isKeyInTree(Node* currentNode, const int key);

// Функция возвращает значение элемента с ключом key, лежащего в дереве tree.
// Функция принимает указатель на корень дерева tree и ключ key.
// Вовращает NULL, если элемент с данным ключом в дереве не найден.
// Если же элемент найден, функция вернет значение элемента - указатель на строку value.
const char* findInTree(Node* currentNode, const int key);

// Функция удаляет из дерева tree элемент с ключом key.
// Принимает указатель на корень дерева root
// и указатель на текущий узел (тоже корень дерева) currentNode, ключ key.
void removeFromTree(Node* root, Node* currentNode, const int key);

// Функция по данному значению узла возвращает значение, лежащее в нем.
const char* getValueFromTree(Node* currentNode);

// Функция возвращает ключ данного узла.
const int getKeyFromTree(Node* currentNode);

// Функция возвращает указатель на правого сына данного узла.
Node* getRightChild(Node* currentNode);

// Функция возвращает указатель на левого сына данного узла.
Node* getLeftChild(Node* currentNode);

Node* rotateLeft(Node* currentNode);

Node* rotateRight(Node* currentNode);

Node* bigRotateLeft(Node* currentNode);

Node* bigRotateRight(Node* currentNode);

Node* balance(Node* currentNode);





