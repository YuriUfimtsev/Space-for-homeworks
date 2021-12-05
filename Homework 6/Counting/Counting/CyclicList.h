#pragma once

#include <stdbool.h>

typedef struct CyclicList CyclicList;

typedef struct Position Position;

// Функция создает список - возвращает указатель на начало списка.
CyclicList* createCyclicList();

// Функция удаляет список. Принимает на вход указатель на голову списка.
void deleteCyclicList(CyclicList* cyclicList);

// Функция удаляет элемент в списке.
// Принимает на вход указатель на элемент списка.
void deletePosition(Position* position);

// Функция добавляет элемент со значением value в конец списка.
// Принимает на вход указатель на голову списка, значение, которое нужно добавить,
// и указатель на последний элемент списка.
void addToTheEnd(CyclicList* cyclicList, int value, Position* lastPosition);

// Функция возвращает указатель на первый элемент списка. Принимает указатель на голову списка.
Position* first(CyclicList* cyclicList);

// Функция возвращает указатель на следующий элемент списка. Принимает указатель на текущий элемент списка.
void next(Position* position);

// Функция возвращает true, если передаваемое значение
// - указатель на элемент списка - является указателем на последний элемент списка.
// false - если передаваемое значение - указатель на элемент списка -
// не является указателем на последний элемент списка.
bool last(Position* position, CyclicList* cyclicList);

// Функция возвращает значение value, лежащее в данном элементе списка.
// Функция принимает указатель на голову списка и указатель на элемент списка.
int getValue(CyclicList* cyclicList, Position* position);

// Функция проверяет, есть ли в списке элемент с данным значением value.
// Функция принимает указатель на голову списка и значение value.
// Возвращает true, если элемент с таким значением присутсвует в списке.
// Возвращает false иначе.
bool valueInCyclicList(CyclicList* cyclicList, int value);

// Функция удаляет элемент со значением value из списка.
// Функция принимает указатель на голову списка.
// Также функция принимает указатель на элемент списка, который нужно удалить.
void deleteValueFromTheNextPosition(CyclicList* cyclicList, Position* position);

// Функция принимает указатель на голову списка, возвращает размер (кол-во элементов) списка.
int getSizeOfCyclicList(CyclicList* cyclicList);