#pragma once

typedef struct PriorityQueue PriorityQueue;

typedef struct PriorityQueueElement PriorityQueueElement;

// Функция создает очередь с приоритетами.
// Возвращает указатель на нее.
PriorityQueue* createPriorityQueue();

// Функция добавляет элемент в очередь с приоритетами.
// Принимает на вход значение, численный приоритет, и указатель на очередь.
// Возвращает 0, если добавление прошло успешно. 0 - иначе.
int enqueue(const int value, const int priority, PriorityQueue* priorityQueue);

// Функция удаляет элемент с наивысышим приоритетом из очереди.
// Принимает указатель на очередь. Возвращает значение элемента.
int dequeue(PriorityQueue* priorityQueue);

// Функция удаляет очередь с приоритетами, принимает указатель на очередь.
void deletePriorityQueue(PriorityQueue* priorityQueue);

// Функция возвращает значение элемента с наивысышим приоритетом в очереди.
// Принимает указатель на очередь.
int getTopOfPriorityQueue(PriorityQueue* priorityQueue);