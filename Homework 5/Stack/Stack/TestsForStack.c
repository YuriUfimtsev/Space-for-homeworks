#include <stdbool.h>
#include <stdio.h>

#include "Stack.h"

bool checkOfPushAndPop(StackElement** head)
{
    bool checkOfCorrectWork = true;
    for (int i = 1; i < 11; ++i)
    {
        push(head, i, &checkOfCorrectWork);
        if (!checkOfCorrectWork)
        {
            return false;
        }
    }
    for (int i = 10; i > 0; --i)
    {
        if (i != pop(head, &checkOfCorrectWork))
        {
            return false;
        }
    }
    return true;
}

bool checkOfTop(StackElement** head)
{
    bool checkOfCorrectWork = true;
    push(head, 300, &checkOfCorrectWork);
    if (!checkOfCorrectWork)
    {
        return false;
    }
    return top(head, &checkOfCorrectWork) == 300;
}

bool checkOfPopFromEmptyStack(StackElement** head)
{
    bool checkOfCorrectWork = true;
    return pop(head, &checkOfCorrectWork) == 0;
}

bool checkOfIsEmpty(StackElement** head)
{
    return isEmpty(*head);
}

bool checkOfDeletingStack(StackElement** head)
{
    bool checkOfCorrectWork = true;
    push(head, 67, &checkOfCorrectWork);
    push(head, 33, &checkOfCorrectWork);
    if (!checkOfCorrectWork)
    {
        return false;
    }
    deleteStack(head, &checkOfCorrectWork);
    if (!checkOfCorrectWork)
    {
        return false;
    }
    return isEmpty(*head);
}

bool areTestsPassing(StackElement** head)
{
    return !checkOfPushAndPop(head) || !checkOfPopFromEmptyStack(head) || !checkOfIsEmpty(head)
        || !checkOfDeletingStack(head) || !checkOfTop(head) ? false : true;
}