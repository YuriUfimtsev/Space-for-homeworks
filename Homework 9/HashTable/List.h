#pragma once

#include <stdbool.h>

typedef struct List List;

typedef struct Position Position;

typedef struct ListElement ListElement;

// ������� ���������� ����� ���������, ������� � ������.
// ��������� ��������� �� ������ ������.
int getNumberOfListElements(List* list);

// ������� ���������� �������, ����������� � ������� ������� ������.
// ��������� ��������� �� ������� ������� � ������
const char* getData(Position* position);

// ������� ���������� �������� numberOfRepetitions ��� ������� ��������.
// ��������� ��������� �� ������ � �������� ��������.
int getNumberOfRepetitionsByHash(const char* data, List* list);

// ������� ���������� �������� numberOfRepetitions ��� ������� ��������.
// ��������� ��������� �� ������� ������.
int getNumberOfRepetitionsByPosition(Position* listElement);

// ������� ������� ������ - ���������� ��������� �� ������ ������.
List* createList();

// ������� ������� ������. ��������� ��������� �� ������ ������.
void deleteList(List* list);

// ������� ������� ������� � ������. ��������� ��������� �� ������� ������.
void deletePosition(Position* position);

// ������� ���������� ������� ������� �������� ������. ��������� ��������� �� ������ ������.
Position* first(List* list);

// ������� ���������� ��������� � �������� �������� �� ��������� ������� ������.
// ��������� ��������� �� ������� ������� ������.
void next(Position* position);

// ������� ���������� true, ���� ������������ �������� �������� ���������� �� ��������� ������� ������.
// false �����.
bool last(Position* position);

// ������� ��������� ������� data � ������.
// ��������� ��������� �� ������ ������, �������� �������� data � �������� numberOfRepetitions.
// ������� ���������� true, ���� ������� �������� ������.
// false - ���� ������� ��� ������������ � ������.
// ����� ������������� �������� numberOfRepetitions ������������� �������� ������.
bool addTheDataInList(List* list, int numberOfRepetitions, const char* data);

// ������� ������� ������� data �� ������.
// ��������� ��������� �� ������ ������ � �������� data.
// ���������� true, ���� ������� �� ��������� value ������.
// ������� ���������� false, ���� �������� �� ��������� value � ������ ���.
bool delete(List* list, const char* data);
