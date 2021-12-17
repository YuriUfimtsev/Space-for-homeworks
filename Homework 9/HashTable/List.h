#pragma once

#include <stdbool.h>

typedef struct List List;

typedef struct Position Position;

typedef struct ListElement ListElement;

int getNumberOfListElements(List* list);

const char* getData(Position* listElement);

int getNumberOfRepetitionsByPosition(Position* listElement);

// Функция создает список - возвращает указатель на структуру ListElement - начало списка.
List* createList();

// Функция удаляет список. Принимает на вход указатель на голову списка (на структуру ListElement).
void deleteList(List* list);

// Функция удаляет элемент в списке. Принимает на вход указатель на элемент списка (указатель на указатель на структуру ListElement).
void deletePosition(Position* position);

// Функция возвращает позицию первого элемента списка. Принимает указатель на голову списка.
Position* first(List* list);

// Функция продвигает указатель на элемент списка на следующий элемент списка.
// Принимает указатель на текущий элемент списка.
void next(Position* position);

// Функция возвращает true, если передаваемое значение - указатель на элемент списка - является указателем на последний элемент списка.
// false иначе.
bool last(Position* position);

// Функция возвращает значение value, лежащее в данном элементе списка.
// Функция принимает указатель на голову списка и указатель на элемент списка.
int getValue(List* list, Position* position);

// Функция проверяет, есть ли в списке элемент с данным значением value.
// Функция принимает указатель на голову списка и значение value.
// Возвращает true, если элемент с таким значением присутсвует в списке.
// Возвращает false иначе.
bool valueInList(List* list, int value);

// Функция добавляет элемент со значением value в сортированный список.
// Функция принимает указатель на голову списка и значение value, которое надо добавить.
bool addTheValueInList(List* list, int value, const char* data);

// Функция удаляет элемент со значением value из списка. 
// Функция принимает указатель на голову списка и значение value, которое надо убрать из списка.
// Функция возвращает true, если элемент со значением value удален.
// Функция возвращает false, если элемента со значением value в списке нет.
bool delete(List* list, const char* data);

int getNumberOfRepetitionsByHash(const char* data, List* list);
