#pragma once

#include <stdbool.h>

typedef struct Node Node;

typedef Node Tree;

// ������� ������� ������. ���������� ��������� �� ������ ������.
Tree* buildParseTree(const char* string);

// ������� ��������� �������� ���������, �������� ����� �� ������.
// ������� ��������� ��������� �� ������ ������, � ����� ��������� �� ����������,
// ������� ������������� � ������� �� ����.
int calculateParseTree(const Tree* tree, bool* checkOfDivisionByZero);

// ������� ������� ������. ��������� ��������� �� ������ ������.
void deleteParseTree(Tree* root);

// ������� ��������� ������ ����� ������ � ���������� � ������ ��������� ������.
// ��������� ��������� �� ������ ������, ������,
// � ������� ����� ������� ���������, � ��������� �� ������ ���� ������.
void prefixTraverse(const Tree* parseTree, char* stringForResult, unsigned int* indexForString);

// ������� ������� �� ����� �������� ������, ���������� � ���������� ������� ������.
// ��������� ��������� �� ������ ������.
void printParseTree(const Tree* parseTree);