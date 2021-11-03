#include <stdlib.h>
#include <stdbool.h>

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

void add(List* list, Position* position, int value)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->value = value;
    if (position->position == NULL)
    {
        list->head = newElement;
        return;
    }
    newElement->next = position->position->next;
    position->position->next = newElement;
}

Position* first(List* list)
{
    Position* positionFirst = malloc(sizeof(Position));
    positionFirst->position = list->head;
    return positionFirst;
}

Position* next(Position* position)
{
    Position* newPosition = malloc(sizeof(Position));
    newPosition->position = position->position->next;
    return newPosition;
}

bool last(Position* position)
{
    return position->position == NULL;
}

int getValue(List* list, Position* position)
{
    return position->position->value;
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
    Position* i = first(list);
    Position* j = next(i);
    while (j->position != NULL && value > getValue(list, j))
    {
        i = next(i);
        j = next(j);
    }
    if (list->head->next == NULL)
    {
        if (value < getValue(list, first(list)))
        {
            newElement->next = list->head;
            list->head = newElement;
            return;
        }
    }
    if (j->position == NULL)
    {
        i->position->next = newElement;
        return;
    }
    if (i->position == first(list)->position && value < getValue(list, first(list)))
    {
        newElement->next = list->head;
        list->head = newElement;
        return;
    }
    newElement->next = i->position->next;
    i->position->next = newElement;
}

void delete(List* list, int value)
{
    Position* i = first(list);
    if (getValue(list, i) == value)
    {
        list->head = i->position->next;
        deletePosition(i);
        return;
    }
    Position* j = next(i);
    while (!last(j) && getValue(list, j) != value)
    {
        i = next(i);
        j = next(i);
    }
    if (last(j))
    {
        i->position->next = NULL;
        deletePosition(j);
        return;
    }
    i->position->next = j->position->next;
    deletePosition(j);
}