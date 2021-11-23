#include <stdlib.h>
#include <stdbool.h>

#include "../LIst/List.h"

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
    if (positionFirst == NULL)
    {
        return NULL;
    }
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

void addFirst(List* list, const int value)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return;
    }
    newElement->value = value;
    if (list->head == NULL)
    {
        list->head = newElement;
        return;
    }
    newElement->next = list->head;
    list->head = newElement;
}

void addLast(List* list, const int value)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return;
    }
    newElement->value = value;
    if (list->head == NULL)
    {
        list->head = newElement;
        return;
    }
    Position* position = malloc(sizeof(Position));
    if (position == NULL)
    {
        return;
    }
    position->position = list->head;
    while (position->position->next != NULL)
    {
        next(position);
    }
    position->position->next = newElement;
    deletePosition(position);
    return;
}