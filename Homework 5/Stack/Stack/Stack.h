#pragma once

#include <stdbool.h>

typedef struct StackElement StackElement;

void push(StackElement** head, int number);

int pop(StackElement** head);

bool isEmpty(StackElement* head);

void deleteStack(StackElement** head);
