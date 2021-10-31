#include <stdbool.h>
#include <stdio.h>

#include "Stack.h"

typedef struct StackElement
{
    int value;
    struct StackElement* next;
} StackElement;

bool checkOfPushAndPop(StackElement** head)
{
    for (int i = 1; i < 11; ++i)
    {
        push(head, i);
    }
    for (int i = 10; i > 0; --i)
    {
        if (i != pop(head))
        {
            return false;
        }
    }
    return true;
}

bool checkOfTop(StackElement** head)
{
    push(&head, 300);
    return top(&head) == 300;
}

bool checkOfPopFromEmptyStack(StackElement** head)
{
    return pop(head) == 0;
}

bool checkOfIsEmpty(StackElement** head)
{
    return isEmpty(*head) == true;
}

bool checkOfDeletingStack(StackElement** head)
{
    push(head, 67);
    push(head, 33);
    deleteStack(head);
    return isEmpty(*head);
}

bool areTestsPassing(StackElement** head)
{
    if (!checkOfPushAndPop(head) || !checkOfPopFromEmptyStack(head) 
        || !checkOfIsEmpty(head) || !checkOfDeletingStack(head) || !checkOfTop(head))
    {
        return false;
    }
    return true;
}