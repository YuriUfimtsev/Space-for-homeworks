#pragma once

#include <stdbool.h>

typedef struct Node {
    int number;
    char symbol;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

// ������� ������� ������ - ������, ��� ������ ����. ���������� ��������� �� ������ ����.
Node* createNode();

// ������� ������� ������, ���������� �� ������ ����. ��������� ��������� �� ����.
void deleteNode(Node* node);

// ������� ������� ��� ������. ������� ������, ���������� ��� ����.
// ��������� ��������� �� ������ ������.
void deleteParseTree(Node* root);

// ������� ��������� ������ ����� ������ � ���������� � ������ ��������� ������.
// ������� ��������� ��������� �� ������ ������,
// ��������� �� ������� �����, ������� ������� ��� �������� � ������
// (��������� ��� ���������� ����������� ������), ����� ������� ��������� ������,
// � ������� ����� ���������� ���������, � ��������� �� ������ ���� ������.
// ����� ���� ������� ��������� ��������� �� ������� ���������� ������ - ����������
// ��� ���������� ���������� ������� � ������������ ������.
void prefixTraverse(Node* parseTree, int* countOfNumbers,
    char* stringForResult, int* indexForString, int* countOfBrackets);

// ������� ���������� ����������� ���-�� ������ � ����� ������.
// ��������� ������, ��������� �� ������ ������
// � ��������� �� ���-�� ���������� ������ � ������.
void addMissingBrackets(char* stringForResult, int* indexForString, int* countOfBrackets);

// ������� ��������� � ������ ������ ������� (������ � �������� ��� ���).
// ������� ��������� ������, � ������� ����� �������� ������, ��������� �� ������ ���� ������,
// ��� ������, ������� ����� ��������, � ������� ����������:
// true - �������� � ����������� ��������, false - ��� �������.
void addToString(char* string, int* indexForString, char symbolToAdding, bool spaceOption);

// ������� ���������, �������� �� ������ ������ ������.
bool isNumberInString(char symbol);

// ������� ���������, �������� �� ������ ������ ����������.
bool isOperatorInString(char symbol);

// ������� ������ ������ ������� ��������������� ���������.
// ��������� ������ � �������������� ���������� � ������ �������� � ������.
// ������� ���������� ��������� �� ������ ���������� ������.
Node* createNewNodeForParseTree(char* stringOfNumbersAndOperators, int* index);

// ������� ��������� �������� ���������, �������� ����� �� ������.
// ������� ��������� ��������� �� ������ ������, � ����� ��������� �� ����������,
// ������� ������������� � ������� �� ����.
int calculateParseTree(Node* tree, bool* checkOfDivisionByZero);