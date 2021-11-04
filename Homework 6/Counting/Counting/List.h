#pragma once

#include <stdbool.h>

typedef struct List List;

typedef struct Position Position;

// ������� ������� ������ - ���������� ��������� �� ��������� ListElement - ������ ������.
List* createList();

// ������� ������� ������. ��������� �� ���� ��������� �� ������ ������ (�� ��������� ListElement).
// ������ �� ����������.
void deleteList(List* list);

// ������� ������� ������� � ������. 
// ��������� �� ���� ��������� �� ������� ������ (��������� �� ��������� �� ��������� ListElement).
// ������ �� ����������.
void deletePosition(Position* position);

void add(List* list, int value);

void addByPosition(List* list, Position* position, int value);

Position* first(List* list);

// ������� ���������� ��������� �� ��������� ������� ������. ��������� ��������� �� ������� ������� ������.
Position* next(Position* position);

// ������� ���������� true, ���� ������������ �������� 
// - ��������� �� ������� ������ - �������� ���������� �� ��������� ������� ������.
// false - ���� ������������ �������� - ��������� �� ������� ������ - �� �������� ���������� �� ��������� ������� ������.
bool last(Position* position, List* list);

// ������� ���������� �������� value, ������� � ������ �������� ������. 
// ������� ��������� ��������� �� ������ ������ � ��������� �� ������� ������.
int getValue(List* list, Position* position);

bool valueInList(List* list, int value);

int sizeOfList(List* list);

// ������� ������� ������� �� ��������� value �� ������. 
// ������� ��������� ��������� �� ������ ������ � �������� value, ������� ���� ������ �� ������.
// ������� ���������� true, ���� ������� �� ��������� value ������.
// ������� ���������� false, ���� �������� �� ��������� value � ������ ���.
bool delete(List* list, int value);

bool last(Position* position, List* list);