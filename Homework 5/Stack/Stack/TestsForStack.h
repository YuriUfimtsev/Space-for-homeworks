#pragma once
#include <stdbool.h>

typedef struct StackElement StackElement;

// Данная функция, как и все, расположенные ниже, принимает адрес указателя на голову стека 
// (указатель на указатель на голову стэка).
// Функция проверяет корректность работы функций стэка push и pop.
bool checkOfPushAndPop(StackElement** head);

// Функция проверяет корректность работы функции стэка top.
bool checkOfTop(StackElement** head);

// Функция проверяет корректность работы функции стэка pop в случае, если стэк пуст.
bool checkOfPopFromEmptyStack(StackElement** head);

// Функция проверяет корректность работы функции стэка isEmpty.
bool checkOfIsEmpty(StackElement** head);

// Функция проверяет корректность работы функции стэка delete.
bool checkOfDeletingStack(StackElement** head);

// Функция проверяет корректность всех функций-тестов для стэка, написанных выше.
bool areTestsPassing(StackElement** head);