#pragma once

#include <stdbool.h>

typedef struct CyclicList CyclicList;

typedef struct Position Position;

// ������� ������� ������ - ���������� ��������� �� ������ ������.
CyclicList* createCyclicList();

// ������� ������� ������. ��������� �� ���� ��������� �� ������ ������.
void deleteCyclicList(CyclicList* cyclicList);

// ������� ������� ������� � ������.
// ��������� �� ���� ��������� �� ������� ������.
void deletePosition(Position* position);

// ������� ��������� ������� �� ��������� value � ����� ������.
// ��������� �� ���� ��������� �� ������ ������, ��������, ������� ����� ��������,
// � ��������� �� ��������� ������� ������.
void addToTheEnd(CyclicList* cyclicList, int value, Position* lastPosition);

// ������� ���������� ��������� �� ������ ������� ������. ��������� ��������� �� ������ ������.
Position* first(CyclicList* cyclicList);

// ������� ���������� ��������� �� ��������� ������� ������. ��������� ��������� �� ������� ������� ������.
void next(Position* position);

// ������� ���������� true, ���� ������������ ��������
// - ��������� �� ������� ������ - �������� ���������� �� ��������� ������� ������.
// false - ���� ������������ �������� - ��������� �� ������� ������ -
// �� �������� ���������� �� ��������� ������� ������.
bool last(Position* position, CyclicList* cyclicList);

// ������� ���������� �������� value, ������� � ������ �������� ������.
// ������� ��������� ��������� �� ������ ������ � ��������� �� ������� ������.
int getValue(CyclicList* cyclicList, Position* position);

// ������� ���������, ���� �� � ������ ������� � ������ ��������� value.
// ������� ��������� ��������� �� ������ ������ � �������� value.
// ���������� true, ���� ������� � ����� ��������� ����������� � ������.
// ���������� false �����.
bool valueInCyclicList(CyclicList* cyclicList, int value);

// ������� ������� ������� �� ��������� value �� ������.
// ������� ��������� ��������� �� ������ ������.
// ����� ������� ��������� ��������� �� ������� ������, ������� ����� �������.
void deleteValueFromTheNextPosition(CyclicList* cyclicList, Position* position);

// ������� ��������� ��������� �� ������ ������, ���������� ������ (���-�� ���������) ������.
int getSizeOfCyclicList(CyclicList* cyclicList);