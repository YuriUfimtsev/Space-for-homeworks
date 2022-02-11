#pragma warning(disable: 4996)

#include <stdlib.h>
#include <stdbool.h>

#include "../Counting/CyclicList.h"

typedef struct ListElement
{
    int value;
    struct ListElement* next;
} ListElement;

typedef struct CyclicList
{
    ListElement* head;
    int sizeOfCyclicList;
} CyclicList;

typedef struct Position
{
    ListElement* position;
} Position;

CyclicList* createCyclicList()
{
    return calloc(1, sizeof(CyclicList));
}

void deleteCyclicList(CyclicList* cyclicList)
{
    ListElement* position = cyclicList->head;
    ListElement* headOfListToCompare = cyclicList->head;
    while (position->next != headOfListToCompare)
    {
        cyclicList->head = cyclicList->head->next;
        free(position);
        position = cyclicList->head;
    }
    free(position);
    free(cyclicList);
}

void deletePosition(Position* position)
{
    free(position);
}

Position* first(CyclicList* cyclicList)
{
    Position* positionFirst = malloc(sizeof(Position));
    if (positionFirst == NULL)
    {
        return NULL;
    }
    positionFirst->position = cyclicList->head;
    return positionFirst;
}

void next(Position* position)
{
    position->position = position->position->next;
}

bool last(Position* position, CyclicList* cyclicList)
{
    return position->position->next == cyclicList->head;
}

void addToTheEnd(CyclicList* cyclicList, int value, Position* lastPosition)
{
    if (lastPosition == NULL)
    {
        return;
    }
    ListElement* newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return;
    }
    newElement->value = value;
    if (cyclicList->head == NULL)
    {
        cyclicList->head = newElement;
        newElement->next = cyclicList->head;
        lastPosition->position = cyclicList->head;
        ++(cyclicList->sizeOfCyclicList);
        return;
    }
    if (lastPosition->position->next != cyclicList->head)
    {
        while (lastPosition->position->next != cyclicList->head)
        {
            lastPosition->position = lastPosition->position->next;
        }
    }
    newElement->next = cyclicList->head;
    lastPosition->position->next = newElement;
    next(lastPosition);
    ++(cyclicList->sizeOfCyclicList);
}

int getValue(CyclicList* cyclicList, Position* position)
{
    return position->position->value;
}

bool valueInCyclicList(CyclicList* cyclicList, int value)
{
    Position* i = first(cyclicList);
    while (!last(i, cyclicList))
    {
        if (getValue(cyclicList, i) == value)
        {
            deletePosition(i);
            return true;
        }
        next(i);
    }
    const int result = getValue(cyclicList, i);
    deletePosition(i);
    return result == value;
}

void deleteValueFromTheNextPosition(CyclicList* cyclicList, Position* position)
{
    if (position->position->next == cyclicList->head)
    {
        if (cyclicList->sizeOfCyclicList == 2)
        {

            cyclicList->head->value = position->position->value;
            ListElement* elementForRemoving = cyclicList->head->next;
            cyclicList->head->next = cyclicList->head;
            free(elementForRemoving);
            --(cyclicList->sizeOfCyclicList);
            return;
        }
        else
        {
            cyclicList->head->value = cyclicList->head->next->value;
            ListElement* elementForRemoving = cyclicList->head->next;
            cyclicList->head->next = cyclicList->head->next->next;
            free(elementForRemoving);
            --(cyclicList->sizeOfCyclicList);
            return;
        }
    }
    ListElement* elementForRemoving = position->position->next;
    position->position->next = position->position->next->next;
    free(elementForRemoving);
    --(cyclicList->sizeOfCyclicList);
    return;
}

int getSizeOfCyclicList(CyclicList* cyclicList)
{
    return cyclicList->sizeOfCyclicList;
}