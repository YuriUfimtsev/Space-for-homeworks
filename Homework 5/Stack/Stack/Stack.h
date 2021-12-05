#pragma once

#include <stdbool.h>

typedef struct StackElement StackElement;

// ������ �������, ��� � ���, ������������� ����, ��������� ����� ��������� �� ������ ����� 
// (��������� �� ��������� �� ������ �����).
// ����� ������� ��������� �����, ������� ���������� �������� � ���� � ��������� �� ���������� ���� bool 
// (� ������� ������ checkOfCorrectWork ������ ����� false).
// � ������ ���� ������ � ������� �� ����������, �������� 
// ���������� checkOfCorrectWork �� ���������.
// ��������� �� ���������� ���� bool ��������� ��� �������, ���������� ����, ����� isEmpty().
// ������� number ���������� � ����.
void push(StackElement** head, int number, bool* checkOfCorrectWork);

// ������� ������� ������ ������� �����.
// ������� ���������� �������� ���������� ��������.
int pop(StackElement** head, bool* checkOfCorrectWork);

// ������� ���������� �������� ������� �������� ����� (��������).
int top(StackElement** head, bool* checkOfCorrectWork);

// ������� ���������, ���� �� ����.
// � ������, ���� ���� ����, ������������ �������� true.
bool isEmpty(StackElement* head);

// ������� ������� ���� (�� ����� ��� ����������).
void deleteStack(StackElement** head, bool* checkOfCorrectWork);
