#pragma once

#include <stdbool.h>

typedef struct StackElement StackElement;

// Данная функция, как и все, расположенные ниже, принимает адрес указателя на голову стека 
// (указатель на указатель на голову стэка).
// Также функция принимает число, которое необходимо положить в стэк и указатель на переменную типа bool 
// (в случает ошибки checkOfCorrectWork станет равно false).
// В случае если ошибки в функции не произойдет, значение 
// переменной checkOfCorrectWork не изменится.
// Указатель на переменную типа bool принимают все функции, написанные ниже, кроме isEmpty().
// Элемент number помещается в стэк.
void push(StackElement** head, int number, bool* checkOfCorrectWork);

// Функция удаляет первый элемент стэка.
// Функция возвращает значение удаленного элемента.
int pop(StackElement** head, bool* checkOfCorrectWork);

// Функция возвращает значение первого элемента стэка (верхнего).
int top(StackElement** head, bool* checkOfCorrectWork);

// Функция проверяет, пуст ли стэк.
// В случае, если стэк пуст, возвращается значение true.
bool isEmpty(StackElement* head);

// Функция удаляет стэк (со всеми его элементами).
void deleteStack(StackElement** head, bool* checkOfCorrectWork);
