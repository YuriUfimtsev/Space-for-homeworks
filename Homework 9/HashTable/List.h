#pragma once

#include <stdbool.h>

typedef struct List List;

typedef struct Position Position;

typedef struct ListElement ListElement;

// Функция возвращает число элементов, лежащих в списке.
// Принимает указатель на голову списка.
int getNumberOfListElements(List* list);

// Функция возвращает элемент, находящийся в текущей позиции списка.
// Принимает указатель на текущую позицию в списке
const char* getData(Position* position);

// Функция возвращает параметр numberOfRepetitions для данного элемента.
// Принимает указатель на список и значение элемента.
int getNumberOfRepetitionsByHash(const char* data, List* list);

// Функция возвращает параметр numberOfRepetitions для данного элемента.
// Принимает указатель на элемент списка.
int getNumberOfRepetitionsByPosition(Position* listElement);

// Функция создает список - возвращает указатель на голову списка.
List* createList();

// Функция удаляет список. Принимает указатель на голову списка.
void deleteList(List* list);

// Функция удаляет элемент в списке. Принимает указатель на элемент списка.
void deletePosition(Position* position);

// Функция возвращает позицию первого элемента списка. Принимает указатель на голову списка.
Position* first(List* list);

// Функция продвигает указатель с текущего элемента на следующий элемент списка.
// Принимает указатель на текущий элемент списка.
void next(Position* position);

// Функция возвращает true, если передаваемое значение является указателем на последний элемент списка.
// false иначе.
bool last(Position* position);

// Функция добавляет элемент data в список.
// Принимает указатель на голову списка, значение элемента data и параметр numberOfRepetitions.
// Функция возвращает true, если элемент добавлен список.
// false - если элемент уже присутствует в списке.
// Тогда увеличивается параметр numberOfRepetitions существующего элемента списка.
bool addTheDataInList(List* list, int numberOfRepetitions, const char* data);

// Функция удаляет элемент data из списка.
// Принимает указатель на голову списка и значение data.
// Возвращает true, если элемент со значением value удален.
// Функция возвращает false, если элемента со значением value в списке нет.
bool delete(List* list, const char* data);
