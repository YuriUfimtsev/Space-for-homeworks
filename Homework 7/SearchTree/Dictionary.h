#pragma once

typedef struct Node Dictionary;

// Словарь и дерево - синонимы, так как обозначают одну и ту же структуру.

// Функция создает словарь. Возвращает указатель на первый элемент словаря.
Dictionary* createDictionary();

//// Функция добавляет элемент с ключом key и значением value в словарь.
// Принимает указатель на корень дерева (первый элемент словаря),
// ключ key и указатель на строку value.
void addToDictionary(Dictionary* dictionary, const int key, const char* value);

// Функция возвращает значение элемента с ключом key, лежащего в словаре.
// Функция принимает указатель на корень дерева (первый элемент словаря) и ключ key.
// Вовращает NULL, если элемент с данным ключом в словаре не найден.
// Если же элемент найден, функция вернет значение элемента - указатель на строку value.
const char* getValueFromDictionary(Dictionary* dictionary, const int key, bool* keyInDictionary);

// Функция проверяет, есть ли в словаре элемент с ключом key.
// Принимает указатель на корень дерева (первый элемент словаря), ключ key.
// Возвращает true, если элемент найден и false - если не найден.
bool isKeyInDictionary(Dictionary* dictionary, const int key);

// Функция удаляет из словаря элемент с ключом key. 
// Принимает указатель на узел дерева tree (элемент словаря) и ключ key.
void removeFromDictionary(Dictionary* dictionary, const int key);

// Функция удаляет словарь. Очищает память, выделенную под него.
// Принимает указатель на корень дерева (первый элемент словаря).
void deleteDictionary(Dictionary* dictionary);
