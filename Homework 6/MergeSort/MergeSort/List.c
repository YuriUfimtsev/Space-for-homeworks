#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct Entry
{
    char name[15];
    char phone[15];
}Entry;

typedef struct ListElement
{
    Entry data;
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

void add(List* list, const char name[], const char phone[])
{
    ListElement* newElement = (ListElement*)calloc(1, sizeof(ListElement));
    strcpy(newElement->data.name, name);
    strcpy(newElement->data.phone, phone);
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

Entry getData(List* list, Position* position)
{
    return position->position->data;
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