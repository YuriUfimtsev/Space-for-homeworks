#pragma once

#define MAX_SIZE_OF_STRING 30

typedef struct Node Dictionary;

// Функция создает словарь. Возвращает указатель на первый элемент словаря.
Dictionary* createDictionary();

//// Функция добавляет элемент с ключом key и значением value в словарь.
// Принимает указатель на первый элемент словаря,
// ключ key и указатель на строку value.
void addToDictionary(Dictionary* dictionary, const int key, const char* value);

// Функция возвращает значение элемента с ключом key, лежащего в словаре.
// Функция принимает указатель на первый элемент словаря и ключ key.
// Вовращает NULL, если элемент с данным ключом в словаре не найден.
// Если же элемент найден, функция вернет значение элемента - указатель на строку value.
const char* getValueFromDictionary(Dictionary* dictionary, const int key, bool* keyInDictionary);

// Функция проверяет, есть ли в словаре элемент с ключом key.
// Принимает указатель на первый элемент словаря, ключ key.
// Возвращает true, если элемент найден, false иначе.
bool isKeyInDictionary(Dictionary* dictionary, const int key);

// Функция удаляет из словаря элемент с ключом key. 
// Принимает указатель на элемент словаря и ключ key.
void removeFromDictionary(Dictionary* dictionary, const int key);

// Функция удаляет словарь. Очищает память, выделенную под него.
// Принимает указатель на первый элемент словаря.
void deleteDictionary(Dictionary* dictionary);
