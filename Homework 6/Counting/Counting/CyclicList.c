#include <stdlib.h>
#include <stdbool.h>

#include "../Counting/CyclicList.h"

typedef struct ListElement
{
    int value;
    struct ListElement* next;
} ListElement;

typedef struct cyclicList
{
    ListElement* head;
} cyclicList;

typedef struct Position
{
    ListElement* position;
} Position;

cyclicList* createCyclicList()
{
    return calloc(1, sizeof(cyclicList));
}

void deleteCyclicList(cyclicList* cyclicList)
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

Position* first(cyclicList* cyclicList)
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

bool last(Position* position, cyclicList* cyclicList)
{
    return position->position->next == cyclicList->head;
}

void addToTheEnd(cyclicList* cyclicList, int value, Position* lastPosition, int* sizeOfCyclicList)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        ++(*sizeOfCyclicList);
        return;
    }
    newElement->value = value;
    if (cyclicList->head == NULL)
    {
        cyclicList->head = newElement;
        newElement->next = cyclicList->head;
        lastPosition->position = cyclicList->head;
        ++(*sizeOfCyclicList);
        return;
    }
    newElement->next = cyclicList->head;
    lastPosition->position->next = newElement;
    next(lastPosition);
    ++(*sizeOfCyclicList);
}

int getValue(cyclicList* cyclicList, Position* position)
{
    return position->position->value;
}

bool valueInCyclicList(cyclicList* cyclicList, int value)
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

bool delete(cyclicList* cyclicList, int value, Position* position, int* sizeOfCyclicList)
{
    if (!valueInCyclicList(cyclicList, value))
    {
        return false;
    }
    Position* i = first(cyclicList);
    if (getValue(cyclicList, i) == value)
    {
        cyclicList->head = i->position->next;
        ListElement* ListElementForRemoving = i->position;
        Position* positionForRemoving = i;
        i = first(cyclicList);
        Position* j = first(cyclicList);
        next(j);
        while (!last(j, cyclicList))
        {
            next(i);
            next(j);
        }
        i->position->next = cyclicList->head;
        next(position);
        free(ListElementForRemoving);
        deletePosition(positionForRemoving);
        deletePosition(i);
        deletePosition(j);
        --(*sizeOfCyclicList);
        return true;
    }
    Position* j = first(cyclicList);
    next(j);
    while (!last(j, cyclicList) && getValue(cyclicList, j) != value)
    {
        next(j);
        next(i);
    }
    i->position->next = j->position->next;
    next(position);
    free(j->position);
    deletePosition(j);
    deletePosition(i);
    --(*sizeOfCyclicList);
    return true;
}