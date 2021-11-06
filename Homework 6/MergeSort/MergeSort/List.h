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
void add(List* list,  int value);

void addByPosition(List* list, Position* position, int value);

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
bool deleteElement(List* list, int value);

// ������� ��������� ������ ������ (���������� ���������).
// ��������� �� ���� ��������� �� ������ ������.
// ���������� ������ ������.
int sizeOfList(List* list);

bool isEmpty(List* list);

void addInHead(List* list, int value);

int indexFromPosition(List* list, Position* position);

void deleteElementByPosition(List* list, Position* position);

Position* getPositionFromValue(List* list, int value);

Position* getPositionFromIndex(List* list, int index);