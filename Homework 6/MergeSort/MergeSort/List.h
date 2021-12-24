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

// Функция создает список - возвращает указатель на начало списка.
List* createList();

// Функция удаляет список. Принимает на вход указатель на голову списка.
void deleteList(List* list);

// Функция удаляет элемент в списке. Принимает на вход указатель на элемент списка
void deletePosition(Position* position);

// Функция добавляет новый элемент - а именно строки name и phone - в конец списка.
// Принимает на вход указатель на голову списка, строки name и phone.
void add(List* list, const char name[], const char phone[]);

// Функция возвращает указатель на первый элемент списка. Принимает указатель на голову списка.
Position* first(List* list);

// Функция продвигает указатель на следующий элемент списка. Принимает указатель на текущий элемент списка.
void next(Position* position);

// Функция возвращает true, если передаваемое значение
// - указатель на элемент списка - является указателем на последний элемент списка.
// false иначе.
bool last(Position* position);

// Функция принимает указатель на голову списка и указатель на элемент списка.
// Функция возвращает структуру Entry.
Entry getData(List* list, Position* position);

// Функция принимает указатель на голову списка, фозвращает размер (кол-во элементов) списка.
int getSizeOfList(List* list);