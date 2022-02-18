#pragma once

#include <stdbool.h>

typedef struct Node Node;

typedef Node Tree;

// Функция создает дерево. Возвращает указатель на корень дерева.
Tree* buildParseTree(const char* string);

// Функция вычисляет значение выражения, выполняя обход по дереву.
// Функция принимает указатель на корень дерева, а также указатель на переменную,
// которая сигнализирует о делении на ноль.
int calculateParseTree(const Tree* tree, bool* checkOfDivisionByZero);

// Функция удаляет дерево. Принимает указатель на корень дерева.
void deleteParseTree(Tree* root);

// Функция выполняет прямой обход дерева и записывает в строку результат обхода.
// Принимает указатель на корень дерева, строку,
// в которую будет записан результат, и указатель на индекс этой строки.
void prefixTraverse(const Tree* parseTree, char* stringForResult, unsigned int* indexForString);

// Функция выводит на экран элементы дерева, полученные в результате прямого обхода.
// Принимает указатель на корень дерева.
void printParseTree(const Tree* parseTree);