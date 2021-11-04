#include <stdio.h>
#include <stdbool.h>

#include "List.h"

int main()
{
    List* cyclicList = createList();

    deleteList(cyclicList);
}
