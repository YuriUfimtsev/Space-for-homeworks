#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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
    return (List*)calloc(1, sizeof(List));
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
    Position* positionFirst = (Position*)malloc(sizeof(Position));
    positionFirst->position = list->head;
    return positionFirst;
}

Position* next(Position* position)
{
    Position* newPosition = (Position*)malloc(sizeof(Position));
    newPosition->position = position->position->next;
    return newPosition;
}

bool last(Position* position)
{
    return position->position == NULL;
}

void addByPosition(List* list, Position* position, int value)
{
    ListElement* newElement = (ListElement*)calloc(1, sizeof(ListElement));
    newElement->value = value;
    if (list->head == NULL)
    {
        list->head = newElement;
        return;
    }
    newElement->next = position->position->next;
    position->position->next = newElement;
}

void addInHead(List* list, int value)
{
    ListElement* newElement = (ListElement*)calloc(1, sizeof(ListElement));
    newElement->value = value;
    if (list->head == NULL)
    {
       list->head = newElement;
        return;
    }
    newElement->next = list->head;
    list->head = newElement;
    return;
}


void add(List* list, int value)
{
    ListElement* newElement = (ListElement*)calloc(1, sizeof(ListElement));
    newElement->value = value;
    if (list->head == NULL)
    {
        list->head = newElement;
        return;
    }
    Position* i = first(list);
    while (!last(next(i)))
    {
        i = next(i);
    }
    i->position->next = newElement;
}

int getValue(List* list, Position* position)
{
    return position->position->value;
}

Position* getPositionFromValue(List* list, int value)
{
    Position* i = first(list);
    while (!last(i))
    {
        if (getValue(list, i) == value)
        {
            return i;
        }
        i = next(i);
    }
    if (getValue(list, i) == value)
    {
        return i;
    }
    return -1;
}

Position* getPositionFromIndex(List* list, int index)
{
    Position* i = first(list);
    if (index == 0)
    {
        return i;
    }
    int j = 0;
    while (j < index)
    {
        i = next(i);
        ++j;
    }
    return i;
}


bool valueInList(List* list, int value)
{
    for (Position* i = first(list); !last(i); i = next(i))
    {
        if (getValue(list, i) == value)
        {
            return true;
        }
    }
    return false;
}

bool deleteElement(List* list, int value)
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
        return true;
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
        return true;
    }
    i->position->next = j->position->next;
    deletePosition(j);
    return true;
}

void deleteElementByPosition(List* list, Position* position)
{
    if (last(position))
    {
        return;
    }
    if (last(next(position)))
    {
        position->position->next = NULL;
        deletePosition(next(position));
        return;
    }
    position->position->next = next(position)->position->next;
    deletePosition(next(position));
}

int sizeOfList(List* list)
{
    int counter = 0;
    if (list->head == NULL)
    {
        return 0;
    }
    for (Position* i = first(list); !last(i); i = next(i))
    {
        ++counter;
    }
    return counter;
}

bool isEmpty(List* list)
{
    return list->head == NULL;
}

int indexFromPosition(List* list, Position* position)
{
    int j = 0;
    Position* i = first(list);
    int value = getValue(list, position);
    while (!last(i))
    {
        if (getValue(list, i) == value)
        {
            return j;
        }
        ++j;
        i = next(i);
    }
    if (getValue(list, i) == value)
    {
        return j;
    }
    return -1;
}
