#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../SortedList/SortedList.h"

bool isAddingInSortedListCorrect(const int arrayOfResult[], int array[], int lengthOfArray)
{
    List* sortedList = createList();
    for (int i = 0; i < lengthOfArray; ++i)
    {
        addTheValueInSortedList(sortedList, array[i]);
    }
    int j = 0;
    Position* startPosition = first(sortedList);
    for (Position* i = startPosition; !last(i); next(i))
    {
        if (getValue(sortedList, i) != arrayOfResult[j])
        {
            deletePosition(i);
            deleteList(sortedList);
            return false;
        }
        ++j;
    }
    deleteList(sortedList);
    return true;
}

bool isDeletionFromTheSortedListCorrect(int arrayOfResult[], int array[],
    int lengthOfArray, int elementForRemove)
{
    List* sortedList = createList();
    for (int i = 0; i < lengthOfArray; ++i)
    {
        addTheValueInSortedList(sortedList, array[i]);
    }
    delete(sortedList, elementForRemove);
    int j = 0;
    Position* startPosition = first(sortedList);
    for (Position* i = startPosition; !(last(i)); next(i))
    {
        if (getValue(sortedList, i) != arrayOfResult[j])
        {
            deletePosition(i);
            deleteList(sortedList);
            return false;
        }
        ++j;
    }
    deleteList(sortedList);
    return true;
}

bool standartTestOfAdding()
{
    int array[4] = { 59, 80, 1, 0 };
    int arrayOfResult[4] = { 0, 1, 59, 80 };
    return isAddingInSortedListCorrect(arrayOfResult, array, 4);
}

bool testWithSortedElementsOfAdding()
{
    int array[6] = { 1, 7, 8, 99, 130, 250 };
    int arrayOfResult[6] = { 1, 7, 8, 99, 130, 250 };
    return isAddingInSortedListCorrect(arrayOfResult, array, 6);
}

bool standartTestOfDeleting()
{
    int array[6] = { 18, 34, 20, 48, 60, 1 };
    int arrayOfResult[5] = { 1, 20, 34, 48, 60 };
    return isDeletionFromTheSortedListCorrect(arrayOfResult, array, 6, 18);
}

bool testOfDeletingFromHead()
{
    int array[4] = { 25, 44, 90, 8 };
    int arrayOfResult[3] = { 25, 44, 90 };
    return isDeletionFromTheSortedListCorrect(arrayOfResult, array, 4, 8);
}

int main(int argc, char* argv[])
{
    if (argc == 2 && strcmp(argv[1], "tests_only") == 0)
    {
        return standartTestOfAdding() && testWithSortedElementsOfAdding()
            && standartTestOfDeleting() && testOfDeletingFromHead() ? 0 : -2;
    }
    List* sortedList = createList();
    if (!standartTestOfAdding() || !testWithSortedElementsOfAdding()
        || !standartTestOfDeleting() || !testOfDeletingFromHead())
    {
        printf("Tests failed");
        deleteList(sortedList);
        return -1;
    }
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
            printf("\n%d was added in the sorted list\n", value);
            break;
        case 2:
            scanf("%d", &value);
            printf(delete(sortedList, value) ? "\n%d was deleted from the sorted list"
                : "\nSorted list doesn't contain this element", value);
            break;
        case 3:
            printf("Sorted list contains this elements: ");
            Position* startPosition = first(sortedList);
            for (Position* i = startPosition; !(last(i)); next(i))
            {
                printf("%d ", getValue(sortedList, i));
            }
            break;
        }
    }
    deleteList(sortedList);
}
