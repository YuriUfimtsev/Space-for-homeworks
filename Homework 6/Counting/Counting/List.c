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
    ListElement* headOfListToCompare = list->head;
    while (position->next != headOfListToCompare)
    {
        list->head = list->head->next;
        free(position);
        position = list->head;
    }
    free(position);
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

Position* next(Position* position)
{
    Position* newPosition = malloc(sizeof(Position));
    newPosition->position = position->position->next;
    return newPosition;
}

bool last(Position* position, List* list)
{
    return position->position->next == list->head;
}

void addByPosition(List* list, Position* position, int value)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->value = value;
    if (list->head == NULL)
    {
        list->head = newElement;
        newElement->next = list->head;
        return;
    }
    if (position->position == list->head)
    {
        Position* i = first(list);
        while (!last(i, list))
        {
            i = next(i);
        }
        newElement->next = list->head;
        list->head = newElement;
        i->position->next = list->head;
        return;
    }
    newElement->next = position->position->next;
    position->position->next = newElement;
}

void add(List* list, int value)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->value = value;
    if (list->head == NULL)
    {
        list->head = newElement;
        newElement->next = list->head;
        return;
    }
    Position* i = first(list);
    while (!last(i, list))
    {
        i = next(i);
    }
    newElement->next = list->head;
    i->position->next = newElement;
}

int getValue(List* list, Position* position)
{
    return position->position->value;
}

bool valueInList(List* list, int value)
{
    Position* i = first(list);
    while (!last(i, list))
    {
        if (getValue(list, i) == value)
        {
            return true;
        }
        i = next(i);
    }
    return getValue(list, i) == value ? true : false;
}

int sizeOfList(List* list)
{
    int counter = 0;
    for (Position* i = first(list); !last(i, list); i = next(i))
    {
        getValue(list, i);
        ++counter;
    }
    return counter + 1;
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
        deletePosition(i);
        i = first(list);
        while (!last(next(i), list))
        {
            i = next(i);
        }
        i->position->next = list->head;
        return true;
    }
    Position* j = next(i);
    while (!last(j, list) && getValue(list, j) != value)
    {
        i = next(i);
        j = next(i);
    }
    i->position->next = j->position->next;
    deletePosition(j);
    return true;
}