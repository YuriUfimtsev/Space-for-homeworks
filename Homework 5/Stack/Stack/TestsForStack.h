#pragma once
#include <stdbool.h>

#include "Stack.h"

// ������ �������, ��� � ���, ������������� ����, ��������� ����� ��������� �� ������ ����� 
// (��������� �� ��������� �� ������ �����).
// ������� ��������� ������������ ������ ������� ����� push � pop.
bool checkOfPushAndPop(StackElement** head);

// ������� ��������� ������������ ������ ������� ����� top.
bool checkOfTop(StackElement** head);

// ������� ��������� ������������ ������ ������� ����� pop � ������, ���� ���� ����.
bool checkOfPopFromEmptyStack(StackElement** head);

// ������� ��������� ������������ ������ ������� ����� isEmpty.
bool checkOfIsEmpty(StackElement** head);

// ������� ��������� ������������ ������ ������� ����� delete.
bool checkOfDeletingStack(StackElement** head);

//������� ��������� ������������ ���������� ���� ������.
bool areTestsPassing(StackElement** head);

