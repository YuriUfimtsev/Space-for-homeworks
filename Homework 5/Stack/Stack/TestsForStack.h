#pragma once

#include <stdbool.h>

typedef struct StackElement StackElement;

bool checkOfPushAndPop(StackElement** head);

bool checkOfPopFromEmptyStack(StackElement** head);

bool checkOfIsEmpty(StackElement** head);

bool checkOfDeletingStack(StackElement** head);

bool areTestsPassing(StackElement** head);
