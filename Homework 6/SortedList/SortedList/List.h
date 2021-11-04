#pragma once
#include <stdbool.h>

typedef struct List List;

typedef struct Position Position;

// ������� ������� ������ - ���������� ��������� �� ��������� ListElement - ������ ������.
List* createList();

// ������� ������� ������. ��������� �� ���� ��������� �� ������ ������ (�� ��������� ListElement).
// ������ �� ����������.
void deleteList(List* list);

// ������� ������� ������� � ������. ��������� �� ���� ��������� �� ������� ������ (��������� �� ��������� �� ��������� ListElement).
// ������ �� ����������.
void deletePosition(Position* position);

// ������� ��������� �������� value � ������. 
// ��������� �� ���� ��������� �� ������� ������ , ����������� �������� value � ��������� �� ������ ������.
// ������ �� ����������.
void add(List* list, Position* position, int value);

// ������� ���������� ��������� �� ������ ������� ������. ��������� ��������� �� ������ ������.
Position* first(List* list);

// ������� ���������� ��������� �� ��������� ������� ������. ��������� ��������� �� ������� ������� ������.
Position* next(Position* position);

// ������� ���������� true, ���� ������������ �������� - ��������� �� ������� ������ - �������� ���������� �� ��������� ������� ������.
// false - ���� ������������ �������� - ��������� �� ������� ������ - �� �������� ���������� �� ��������� ������� ������.
bool last(Position* position);

// ������� ���������� �������� value, ������� � ������ �������� ������. 
// ������� ��������� ��������� �� ������ ������ � ��������� �� ������� ������.
int getValue(List* list, Position* position);

// ������� ���������, ���� �� � ������ ������� � ������ ��������� value.
// ������� ��������� ��������� �� ������ ������ � �������� value. 
// ���������� true, ���� ������� � ����� ��������� ����������� � ������. 
// ���������� false, ���� ������� � ����� ��������� ����������� � ������.
bool valueInList(List* list, int value);

// ������� ��������� ������� �� ��������� value � ������������� ������. 
// ������� ��������� ��������� �� ������ ������ � �������� value, ������� ���� ��������.
// ������� ������ �� ����������.
void addTheValueInSortedList(List* list, int value);

// ������� ������� ������� �� ��������� value �� ������. 
// ������� ��������� ��������� �� ������ ������ � �������� value, ������� ���� ������ �� ������.
// ������� ���������� true, ���� ������� �� ��������� value ������.
// ������� ���������� false, ���� �������� �� ��������� value � ������ ���.
bool delete(List* list, int value);