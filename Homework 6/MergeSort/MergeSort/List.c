#include "../MergeSort/List.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Entry
{
    char name[15];
    char phone[15];
} Entry;

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

void next(Position* position)
{
    position->position = position->position->next;
}

bool last(Position* position)
{
    return position->position == NULL;
}

void add(List* list, const char name[], const char phone[], int* sizeOfList)
{
    ListElement* newElement = (ListElement*)calloc(1, sizeof(ListElement));
    strcpy(newElement->data.name, name);
    strcpy(newElement->data.phone, phone);
    if (list->head == NULL)
    {
        list->head = newElement;
        ++(*sizeOfList);
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
    ++(*sizeOfList);
}

Entry getData(List* list, Position* position)
{
    return position->position->data;
}