#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "List.h"
#include "MergeSort.h"
#include "TestsForMergeSort.h"

int main(int argc, char* argv[])
{
    if (argc == 2 && strcmp(argv[1], "tests_only") == 0)
    {
        return testOfMergeSortingByName() ? 0 : -2;
    }
    if (!testOfMergeSortingByName())
    {
        printf("Tests failed");
        return -1;
    }
    FILE* data = fopen("Data.txt", "r");
    if (data == NULL)
    {
        printf("File not found");
        return -1;
    }
    printf("How do you want sorting the notes?\n");
    printf("Enter 0 if you want sorting by phone number.\nEnter 1 if you want sorting by name.\n");
    printf("Your choice: ");
    enum Key key;
    scanf("%d", &key);
    if (key != 0 && key != 1)
    {
        printf("\nIncorrect value\n");
        fclose(data);
        return -1;
    }
    int sizeOfList = 0;
    List* listOfEntries = readEntriesFromFile(data);
    fclose(data);
    List* sortedList = mergeSort(listOfEntries, key);
    printf("\nResult of sorting: \n");
    Position* startedPosition = first(sortedList);
    for (Position* i = startedPosition; !last(i); next(i))
    {
        printf("%s %s \n", getData(sortedList, i).name, getData(sortedList, i).phone);
    }
    deletePosition(startedPosition);
    deleteList(sortedList);
}