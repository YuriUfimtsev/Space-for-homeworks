#include <stdio.h>
#include <stdlib.h>

#include "List.h"

int main()
{
    List* sortedList = createList();
    //if (!Test)
    //{
    //    return -1;
    //}
    int command = 1;
    printf("You can use following commands.\n");
    printf("0 - exit the programme.\n");
    printf("1 - add the value in the sorted list.\n");
    printf("2 - delete the value from the sorted list.\n");
    printf("3 - look to the sorted list elements (print sorted list).\n");
    while (command != 0)
    {
        printf("\nEnter the next command: ");
        scanf("%d", &command);
        int value = 0;
        switch (command)
        {
        case 0:
            break;
        case 1:
            scanf("%d", &value);
            addTheValueInSortedList(sortedList, value);
            break;
        case 2:
            scanf("%d", &value);
            delete(sortedList, value);
            break;
        case 3:
            for (Position* i = first(sortedList); !(last(i)); i = next(i))
            {
                printf("%d ", getValue(sortedList, i));
            }
            break;
        }
    }
    deleteList(sortedList);
}
