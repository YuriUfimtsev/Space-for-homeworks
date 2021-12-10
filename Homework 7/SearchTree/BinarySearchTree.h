#pragma once

#include <stdbool.h>

typedef struct Node Node;

// Функция создает дерево - точнее, его первый узел. Возвращает указатель на данный узел.
Node* createEmptyNode();

// Функция удаляет все дерево. Очищает память, выделенную под него.
// Принимает указатель на корень дерева.
void deleteTree(Node* parent);

// Функция добавляет новый узел с ключом key и значением value в дерево tree.
// Принимает указатель на корень дерева, ключ key и указатель на строку value.
void insertToTree(Node* currentNode, const int key, const char* value);

// Функция проверяет, есть ли в дереве tree элемент с ключом key.
// Принимает указатель на корень дерева, ключ key.
// Возвращает true, если элемент найден и false - если не найден.
bool isKeyInTree(Node* currentNode, const int key);

// Функция возвращает значение элемента с ключом key, лежащего в дереве tree.
// Функция принимает указатель на корень дерева tree и ключ key.
// Вовращает NULL, если элемент с данным ключом в дереве не найден.
// Если же элемент найден, функция вернет значение элемента - указатель на строку value.
const char* findInTree(Node* currentNode, const int key);

// Функция удаляет из дерева tree элемент с ключом key. 
// Принимает указатель на узел дерева tree, указатель на корень дерева root и ключ key.
void removeFromTree(Node* currentNode, Node* parent, const int key);

const char* getValueFromTree(Node* currentNode);

const int getKeyFromTree(Node* currentNode);

Node* getRightChild(Node* currentNode);

Node* getLeftChild(Node* currentNode);

Node* createNode(const int key, const char* value);
