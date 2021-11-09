#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct StackElement
{
    int value;
    struct StackElement* next;
} StackElement;

void push(StackElement** head, int number, bool* checkOfCorrectWork)
{
    StackElement* newStackElement = calloc(1, sizeof(StackElement));
    if (newStackElement == NULL)
    {
        *checkOfCorrectWork = false;
        return;
    }
    newStackElement->value = number;
    newStackElement->next = *head;
    *head = newStackElement;
}

int pop(StackElement** head, bool* checkOfCorrectWork)
{
    if (head == NULL || *head == NULL)
    {
        *checkOfCorrectWork = false;
        return 0;
    }
    StackElement* temporary = *head;
    int value = temporary->value;
    *head = (*head)->next;
    free(temporary);
    return value;
}

int top(StackElement** head, bool* checkOfCorrectWork)
{
    if (head == NULL || *head == NULL)
    {
        *checkOfCorrectWork = false;
        return 0;
    }
    return (*head)->value;
}

bool isEmpty(StackElement* head)
{
    return head == NULL;
}

void deleteStack(StackElement** head, bool* checkOfCorrectWork)
{
    while (!isEmpty(*head))
    {
        pop(head, checkOfCorrectWork);
    }
}