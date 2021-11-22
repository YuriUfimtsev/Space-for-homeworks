#include <stdlib.h>
#include <stdbool.h>

#include "../SortedList/SortedList.h"

typedef struct ListElement
{
    int value;
    struct ListElement* next;
} ListElement;

typedef struct List
{
    ListElement* head;
} List;

typedef struct Position
{
    ListElement* position;
} Position;

List* createList()
{
    return calloc(1, sizeof(List));
}

void deleteList(List* list)
{
    ListElement* position = list->head;
    while (position != NULL)
    {
        list->head = list->head->next;
        free(position);
        position = list->head;
    }
    free(list);
}

void deletePosition(Position* position)
{
    free(position);
}

Position* first(List* list)
{
    Position* positionFirst = malloc(sizeof(Position));
    positionFirst->position = list->head;
    return positionFirst;
}

void next(Position* position)
{
    position->position = position->position->next;
}

bool last(Position* position)
{
    bool const result = position->position == NULL;
    if (result)
    {
        deletePosition(position);
    }
    return result;
}

int getValue(List* list, Position* position)
{
    return position->position->value;
}

bool valueInList(List* list, int value)
{
    Position* startPosition = first(list);
    for (Position* i = startPosition; !last(i); next(i))
    {
        if (getValue(list, i) == value)
        {
            deletePosition(i);
            return true;
        }
    }
    deletePosition(startPosition);
    return false;
}

void addTheValueInSortedList(List* list, int value)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->value = value;
    if (list->head == NULL)
    {
        list->head = newElement;
        return;
    }
    Position* startPosition = first(list);
    if (list->head->next == NULL)
    {
        if (value < getValue(list, startPosition))
        {
            newElement->next = list->head;
            list->head = newElement;
            deletePosition(startPosition);
            return;
        }
    }
    Position* i = first(list);
    Position* j = first(list);
    next(j);
    while (j->position != NULL && value > getValue(list, j))
    {
        next(i);
        next(j);
    }
    if (j->position == NULL)
    {
        i->position->next = newElement;
        deletePosition(i);
        deletePosition(j);
        deletePosition(startPosition);
        return;
    }
    if (i->position == startPosition->position && value < getValue(list, startPosition))
    {
        newElement->next = list->head;
        list->head = newElement;
        deletePosition(i);
        deletePosition(j);
        deletePosition(startPosition);
        return;
    }
    newElement->next = i->position->next;
    i->position->next = newElement;
    deletePosition(i);
    deletePosition(j);
    deletePosition(startPosition);
}

bool delete(List* list, int value)
{
    if (!valueInList(list, value))
    {
        return false;
    }
    Position* i = first(list);
    if (getValue(list, i) == value)
    {
        list->head = i->position->next;
        free(i->position);
        deletePosition(i);
        return true;
    }
    Position* j = first(list);
    next(j);
    while (!last(j) && getValue(list, j) != value)
    {
        next(i);
        next(j);
    }
    if (last(j))
    {
        i->position->next = NULL;
        free(j->position);
        deletePosition(i);
        return true;
    }
    i->position->next = j->position->next;
    deletePosition(i);
    free(j->position);
    deletePosition(j);
    return true;
}