#pragma once

#include "../ParseTree/ParseTree.h"

// Функция проверяет работу функций prefixTraverse и createNewNodeForParseTree.
// Возвращает true, если функции работают правильно.
bool checkOfCreatingParseTree();

// Функция проверяет работу функции calculateParseTree.
// Возвращает true, если calculateParseTree выполняется правильно.
bool checkOfCalculatingParseTree();

// Функция проверяет, насколько успешно выполнены все тесты.
// Возвращает true, если все тесты прошли успешно.
bool areTestsPassed();
