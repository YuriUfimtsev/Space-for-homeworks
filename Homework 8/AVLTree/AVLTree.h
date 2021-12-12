#pragma once

#include <stdbool.h>

typedef struct Node Node;

// Функция создает пустое дерево. Возвращает указатель на данный узел.
Node* createEmptyNode();

// Функция создает дерево с ключем key и значением value в корне.
Node* createNode(const int key, const char* value);

// Функция удаляет все дерево. Очищает память, выделенную под него.
// Принимает указатель на корень дерева.
void deleteAVLTree(Node* parent);

// Функция возвращает значение элемента с ключом key, лежащего в дереве tree.
// Функция принимает указатель на корень дерева tree и ключ key.
// Вовращает NULL, если элемент с данным ключом в дереве не найден.
// Если же элемент найден, функция вернет значение элемента - указатель на строку value.
const char* advancedGetValue(Node* root, const int key);


void advancedInsertToAVLTree(Node** root, const int key, const char* value);

// Функция проверяет, есть ли в дереве tree элемент с ключом key.
// Принимает указатель на корень дерева, ключ key.
// Возвращает true, если элемент найден, false иначе.
bool isKeyInAVLTree(Node* currentNode, const int key);

// Функция удаляет из дерева tree элемент с ключом key.
// Принимает указатель на корень дерева root
// и указатель на текущий узел (тоже корень дерева) currentNode, ключ key.
void advancedRemoveFromAVLTree(Node* root, const int key);

// Функция по данному значению узла возвращает значение, лежащее в нем.
const char* getValueFromAVLTree(Node* currentNode, const int key);


// Функция возвращает ключ данного узла.
const int getKeyFromAVLTree(Node* currentNode);

// Функция возвращает указатель на правого сына данного узла.
Node* getRightChild(Node* currentNode);

// Функция возвращает указатель на левого сына данного узла.
Node* getLeftChild(Node* currentNode);

Node* insertToAVLTree(Node* currentNode, const int key, const char* value, Node* root,
    bool* areBalancesCorrect, bool* isBalance);

char getBalanceFromAVLTree(Node* currentNode);

