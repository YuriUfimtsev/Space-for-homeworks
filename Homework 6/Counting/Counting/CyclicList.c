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

void addByPosition(cyclicList* cyclicList, Position* position, int value)
{
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
        return;
    }
    if (position->position == cyclicList->head)
    {
        Position* i = first(cyclicList);
        while (!last(i, cyclicList))
        {
            next(i);
        }
        newElement->next = cyclicList->head;
        cyclicList->head = newElement;
        i->position->next = cyclicList->head;
        deletePosition(i);
        return;
    }
    newElement->next = position->position->next;
    position->position->next = newElement;
}

void add(cyclicList* cyclicList, int value)
{
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
        return;
    }
    Position* i = first(cyclicList);
    while (!last(i, cyclicList))
    {
        next(i);
    }
    newElement->next = cyclicList->head;
    i->position->next = newElement;
    deletePosition(i);
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

int sizeOfCyclicList(cyclicList* cyclicList)
{
    int counter = 0;
    Position* startPosition = first(cyclicList);
    for (Position* i = startPosition; !last(i, cyclicList); next(i))
    {
        getValue(cyclicList, i);
        ++counter;
    }
    deletePosition(startPosition);
    return counter + 1;
}

bool delete(cyclicList* cyclicList, int value, Position* position)
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
    return true;
}