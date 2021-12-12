#pragma once

#include <stdbool.h>

typedef struct Node Node;

// Функция создает пустое дерево. Возвращает указатель на данный узел.
Node* createEmptyNode();

// Функция создает дерево с ключем key и значением value в корне.
Node* createNode(const int key, const char* value);

// Функция удаляет все дерево.
// Принимает указатель на корень дерева.
void deleteAVLTree(Node* parent);

// Функция возвращает значение элемента с ключом key, лежащего в дереве tree.
// Функция принимает указатель на корень дерева root и ключ key.
// Вовращает NULL, если элемент с данным ключом в дереве не найден.
const char* advancedGetValue(Node* root, const int key);

// Функция добавляет элемент в АВЛ дерево. Принимает адрес указателя на корень дерева,
// ключ key, значениу value, которое необходимо добавить
void advancedInsertToAVLTree(Node** root, const int key, const char* value);

// Функция проверяет, есть ли в дереве tree элемент с ключом key.
// Принимает указатель на корень дерева, ключ key.
// Возвращает true, если элемент найден, false иначе.
bool isKeyInAVLTree(Node* currentNode, const int key);

// Функция удаляет из дерева элемент с ключом key.
// Принимает указатель на корень дерева root, ключ key.
void advancedRemoveFromAVLTree(Node* root, const int key);

// Функция принимает указатель на корень дерева и ключ.
// Возвращет значение, соответствующее этому ключу.
const char* getValueFromAVLTree(Node* currentNode, const int key);

// Функция возвращает ключ данного узла.
const int getKeyFromAVLTree(Node* currentNode);

// Функция возвращает указатель на правого сына данного узла.
Node* getRightChild(Node* currentNode);

// Функция возвращает указатель на левого сына данного узла.
Node* getLeftChild(Node* currentNode);

// Функция возвращает значение баланса данного узла.
char getBalanceFromAVLTree(Node* currentNode);
