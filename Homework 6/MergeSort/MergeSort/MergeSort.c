#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

int main()
{
    List* newList = createList();
    add(newList, first(newList), 1);
    add(newList, first(newList), 3);
    add(newList, first(newList), 8);
    add(newList, first(newList), 4);
    //divideList(newList);
    deleteList(newList);
}

