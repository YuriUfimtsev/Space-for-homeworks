#pragma once
#include <stdbool.h>

typedef struct List List;

typedef struct Position Position;

typedef struct Entry
{
    char name[15];
    char phone[15];
} Entry;

enum Key {
    phoneNumber,
    name
};

// ������� ������� ������ - ���������� ��������� �� ������ ������.
List* createList();

// ������� ������� ������. ��������� �� ���� ��������� �� ������ ������.
void deleteList(List* list);

// ������� ������� ������� � ������. ��������� �� ���� ��������� �� ������� ������
void deletePosition(Position* position);

// ������� ��������� ����� ������� - � ������ ������ name � phone - � ����� ������.
// ��������� �� ���� ��������� �� ������ ������, ������ name � phone.
void add(List* list, const char name[], const char phone[]);

// ������� ���������� ��������� �� ������ ������� ������. ��������� ��������� �� ������ ������.
Position* first(List* list);

// ������� ���������� ��������� �� ��������� ������� ������. ��������� ��������� �� ������� ������� ������.
void next(Position* position);

// ������� ���������� true, ���� ������������ ��������
// - ��������� �� ������� ������ - �������� ���������� �� ��������� ������� ������.
// false �����.
bool last(Position* position);

// ������� ��������� ��������� �� ������ ������ � ��������� �� ������� ������.
// ������� ���������� ��������� Entry.
Entry getData(List* list, Position* position);

// ������� ��������� ��������� �� ������ ������, ���������� ������ (���-�� ���������) ������.
int getSizeOfList(List* list);