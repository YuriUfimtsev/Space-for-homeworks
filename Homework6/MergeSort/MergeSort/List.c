#pragma warning(disable: 4996)

#include "../MergeSort/List.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct ListElement
{
    Entry data;
    struct ListElement* next;
} ListElement;

typedef struct List
{
    ListElement* head;
    int sizeOfList;
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
    return position->position == NULL;
}

void add(List* list, const char name[], const char phone[])
{
    ListElement* newElement = (ListElement*)calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return;
    }
    strcpy_s(newElement->data.name, 15, name);
    strcpy_s(newElement->data.phone, 15, phone);
    if (list->head == NULL)
    {
        list->head = newElement;
        ++(list->sizeOfList);
        return;
    }
    Position* i = first(list);
    Position* j = first(list);
    next(j);
    while (!last(j))
    {
        next(i);
        next(j);
    }
    i->position->next = newElement;
    deletePosition(i);
    deletePosition(j);
    ++(list->sizeOfList);
}

Entry getData(List* list, Position* position)
{
    return position->position->data;
}

int getSizeOfList(List* list)
{
    return list->sizeOfList;
}