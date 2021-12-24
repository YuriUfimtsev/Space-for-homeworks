#pragma once

typedef struct PriorityQueue PriorityQueue;

typedef struct PriorityQueueElement PriorityQueueElement;

// ������� ������� ������� � ������������.
// ���������� ��������� �� ���.
PriorityQueue* createPriorityQueue();

// ������� ��������� ������� � ������� � ������������.
// ��������� �� ���� ��������, ��������� ���������, � ��������� �� �������.
// ���������� 0, ���� ���������� ������ �������. 0 - �����.
int enqueue(const int value, const int priority, PriorityQueue* priorityQueue);

// ������� ������� ������� � ���������� ����������� �� �������.
// ��������� ��������� �� �������. ���������� �������� ��������.
int dequeue(PriorityQueue* priorityQueue);

// ������� ������� ������� � ������������, ��������� ��������� �� �������.
void deletePriorityQueue(PriorityQueue* priorityQueue);

// ������� ���������� �������� �������� � ���������� ����������� � �������.
// ��������� ��������� �� �������.
int getTopOfPriorityQueue(PriorityQueue* priorityQueue);