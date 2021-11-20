#pragma once

#include <stdbool.h>

typedef struct Node {
    int key;
    char* value;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

// Функция создает дерево - точнее, его первый узел. Возвращает указатель на данный узел.
Node* createNode();

// Функция очищает память, выделенную по данный узел. Принимает указатель на узел.
void deleteNode(Node* node);

// Функция удаляет все дерево. Очищает память, выделенную под него.
// Принимает указатель на корень дерева.
void deleteTree(Node* root);

// Функция добавляет новый узел с ключом key и значением value в дерево tree.
// Принимает указатель на корень дерева, ключ key и указатель на строку value.
void insertToTree(Node* tree, const int key, char* value);

// Функция проверяет, есть ли в дереве tree элемент с ключом key.
// Принимает указатель на корень дерева, ключ key.
// Возвращает true, если элемент найден и false - если не найден.
bool isKeyInTree(Node* tree, const int key);

// Функция возвращает значение элемента с ключом key, лежащего в дереве tree.
// Функция принимает указатель на корень дерева tree и ключ key.
// Вовращает NULL, если элемент с данным ключом в дереве не найден.
// Если же элемент найден, функция вернет значение элемента - указатель на строку value.
char* findInTree(Node* tree, const int key);

// Функция удаляет из дерева tree элемент с ключом key. 
// Принимает указатель на узел дерева tree, указатель на корень дерева root и ключ key.
void removeFromTree(Node* tree, Node* root, const int key);
