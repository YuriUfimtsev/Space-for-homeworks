#pragma warning(disable: 4996 6031)

#include <stdio.h>

#include "../LIst/List.h"

List* makeListWithNumbersFromFile(FILE* data)
{
    List* startedList = createList();
    int elementOfList = 0;
    while (!feof(data))
    {
        fscanf(data, "%d", &elementOfList);
        addLast(startedList, elementOfList);
    }
    return startedList;
}

List* makeInvertedList(List* startedList)
{
    List* invertedList = createList();
    Position* startPosition = first(startedList);
    for (Position* i = startPosition; !last(i); next(i))
    {
        int numberForAdding = getValue(startedList, i);
        addFirst(invertedList, numberForAdding);
    }
    return invertedList;
}

void printListElements(List* listForPrintf)
{
    Position* startPosition = first(listForPrintf);
    for (Position* i = startPosition; !last(i); next(i))
    {
        int numberForPrintf = getValue(listForPrintf, i);
        printf("%d ", numberForPrintf);
    }
}

bool testOfMakingListWithNumbersFromFile()
{
    FILE* testData = fopen("TestData", "r");
    int array[5] = { 10, 20, 80, 30, 50 } ;
    List* startedList = makeListWithNumbersFromFile(testData);
    fclose(testData);
    Position* startPosition = first(startedList);
    int indexOfArray = 0;
    for (Position* i = startPosition; !(last(i)); next(i))
    {
        if (array[indexOfArray] != getValue(startedList, i))
        {
            deleteList(startedList);
            deletePosition(i);
            return false;
        }
        ++indexOfArray;
    }
    deleteList(startedList);
    deletePosition(startPosition);
    return true;
}

bool testOfMakingInvertedList()
{
    FILE* testData = fopen("TestData", "r");
    int array[5] = { 50, 30, 80, 20, 10 };
    List* startedList = makeListWithNumbersFromFile(testData);
    fclose(testData);
    List* invertedList = makeInvertedList(startedList);
    deleteList(startedList);
    Position* startPosition = first(invertedList);
    int indexOfArray = 0;
    for (Position* i = startPosition; !(last(i)); next(i))
    {
        if (array[indexOfArray] != getValue(invertedList, i))
        {
            deleteList(invertedList);
            deletePosition(i);
            return false;
        }
        ++indexOfArray;
    }
    deleteList(invertedList);
    deletePosition(startPosition);
    return true;
}

bool areTestsPassing()
{
    return testOfMakingListWithNumbersFromFile() && testOfMakingInvertedList();
}

int main()
{
    if (!areTestsPassing())
    {
        printf("Tests failed");
        return - 1;
    }
    FILE* data = fopen("Data.txt", "r");
    List* startedList = makeListWithNumbersFromFile(data);
    fclose(data);
    Position* startPosition = first(startedList);
    List* invertedList = makeInvertedList(startedList);
    printListElements(invertedList);

    deletePosition(startPosition);
    deleteList(startedList);
    deleteList(invertedList);
}
