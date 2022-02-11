#pragma warning (disable: 4996)

#include <stdio.h>

#include "List.h"
#include"TestsForTask.h"

int main()
{
    if (!areTestsPassing())
    {
        printf("Tests failed");
        return -1;
    }
    FILE* data = fopen("Data.txt", "r");
    List* newList = fillListFromFile(data);
    if (newList == NULL)
    {
        printf("Error of making list");
        return -1;
    }
    fclose(data);
    printf("Non-repeating strings in the file: ");
    printListElements(newList);
    printf("\n");
    deleteList(newList);
}

