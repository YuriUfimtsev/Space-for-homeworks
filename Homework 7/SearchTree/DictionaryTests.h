#pragma once

// Функция проверяет работу функции словаря addToTheDictionary.
// Возвращает true, если элементы в правильном порядке добавляются в словарь.
bool checkOfAddingToTheDictionary();

// Функция проверяет работу функции словаря getValueFromDictionary.
// Возвращает true, если значения элементов в словаре соответствуют значениям,
// которые изначально были у элементов с данными ключами.
bool checkOfGettingValueFromDictionary();

// Функция проверяет работу функции словаря removeFromDictionary.
// Возвращает true, если элементы удаляются из словаря
// и при этом баланс дерева не нарушается.
bool checkOfRemovingFromDictionary();

// Функция проверяет, насколько успешно выполнены все тесты.
// Возвращает true, если все тесты прошли успешно. 
bool areTestsPassing();