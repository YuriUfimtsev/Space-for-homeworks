#pragma once

#include <stdbool.h>

typedef struct List List;

typedef struct Position Position;

// Функция создает список - возвращает указатель на структуру ListElement - начало списка.
List* createList();

// Функция удаляет список. Принимает на вход указатель на голову списка (на структуру ListElement).
// Ничего не возвращает.
void deleteList(List* list);

// Функция удаляет элемент в списке. 
// Принимает на вход указатель на элемент списка (указатель на указатель на структуру ListElement).
// Ничего не возвращает.
void deletePosition(Position* position);

void add(List* list, int value);

void addByPosition(List* list, Position* position, int value);

Position* first(List* list);

// Функция возвращает указатель на следующий элемент списка. Принимает указатель на текущий элемент списка.
Position* next(Position* position);

// Функция возвращает true, если передаваемое значение 
// - указатель на элемент списка - является указателем на последний элемент списка.
// false - если передаваемое значение - указатель на элемент списка - не является указателем на последний элемент списка.
bool last(Position* position, List* list);

// Функция возвращает значение value, лежащее в данном элементе списка. 
// Функция принимает указатель на голову списка и указатель на элемент списка.
int getValue(List* list, Position* position);

bool valueInList(List* list, int value);

int sizeOfList(List* list);

// Функция удаляет элемент со значением value из списка. 
// Функция принимает указатель на голову списка и значение value, которое надо убрать из списка.
// Функция возвращает true, если элемент со значением value удален.
// Функция возвращает false, если элемента со значением value в списке нет.
bool delete(List* list, int value);

bool last(Position* position, List* list);