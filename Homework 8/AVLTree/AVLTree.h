#pragma once

#define valueAndKeySize 30

#include <stdbool.h>

// Структура задает словарь
typedef struct Node Node;

// Функция создает пустой словарь.
Node* createEmptyDictionary();

// Функция создает словарь с элементом: ключ key и значение value.
// Владение переданной памятью(value) словарь не принимает.
Node* createDictionary(const char* key, const char* value);

// Функция удаляет словарь
// Принимает указатель на словарь.
void deleteDictionary(Node* dictionary);

// Функция возвращает значение элемента с ключом key, лежащего в словаре.
// Функция принимает указатель на словарь, ключ key и bool переменную для проверки существования ключа в словаре.
// Вовращает NULL, если элемент с данным ключом в словаре не найден.
const char* getValueFromDictionary(Node* dictionary, const char* key, bool* isKeyInDictionary);

// Функция добавляет элемент в словарь. Принимает адрес указателя на словарь,
// ключ key, значение value, которое необходимо добавить.
// Владение переданной памятью(value) словарь не принимает.
void insertToDictionary(Node** dictionary, const char* key, const char* value);

// Функция проверяет, есть ли в словаре элемент с ключом key.
// Принимает указатель на словарь, ключ key.
// Возвращает true, если элемент найден, false иначе.
bool isKeyInDictionary(Node* currentNode, const char* key);

// Функция удаляет из словаря элемент с ключом key.
// Принимает указатель на словарь, ключ key.
void removeFromDictionary(Node* dictionary, const char* key);

// Функция возвращает ключ данного элемента словаря.
const char* getKeyFromDictionary(Node* dictionaryValue);

// Функция возвращает указатель на правого сына данного узла.
Node* getRightChild(Node* currentNode);

// Функция возвращает указатель на левого сына данного узла.
Node* getLeftChild(Node* currentNode);

// Функция возвращает значение баланса данного элемента словаря.
char getBalanceFromAVLTree(Node* currentNode);

// Функция проверяет, выполнен ли баланс в каждом узле.
bool checkBalance(Node* currentNode);

// Функция возвращает размер словаря.
// И проверяет, выполнен ли инвариант двоичного дерева у Словаря.
int returnSize(Node* currentNode, int* size);
