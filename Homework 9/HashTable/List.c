#include <stdlib.h>
#include <stdbool.h>

#include "List.h"

typedef struct ListElement
{
    int numbersOfRepetition;
    const char* data;
    struct ListElement* next;
} ListElement;

typedef struct List
{
    int numberOfElements;
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
    return position->position->numbersOfRepetition;
}

bool valueInList(List* list, int value)
{
    for (Position* i = first(list); !last(i); next(i))
    {
        if (getValue(list, i) == value)
        {
            deletePosition(i);
            return true;
        }
    }
    return false;
}

void addTheValueInSortedList(List* list, int value)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return;
    }
    newElement->numbersOfRepetition = value;
    if (list->head == NULL)
    {
        list->head = newElement;
        return;
    }
    if (list->head->next == NULL)
    {
        if (value < list->head->numbersOfRepetition)
        {
            newElement->next = list->head;
            list->head = newElement;
            return;
        }
    }
    ListElement* i = list->head;
    while (i->next != NULL && value > i->next->numbersOfRepetition)
    {
        i = i->next;
    }
    if (i->next == NULL)
    {
        i->next = newElement;
        return;
    }
    if (i == list->head && value < list->head->numbersOfRepetition)
    {
        newElement->next = list->head;
        list->head = newElement;
        return;
    }
    newElement->next = i->next;
    i->next = newElement;
}

bool delete(List* list, int value)
{
    if (!valueInList(list, value))
    {
        return false;
    }
    ListElement* i = list->head;
    if (i->numbersOfRepetition == value)
    {
        list->head = i->next;
        free(i);
        return true;
    }
    ListElement* j = list->head->next;
    while (j != NULL && j->numbersOfRepetition != value)
    {
        i = i->next;
        j = j->next;
    }
    if (j == NULL)
    {
        i->next = NULL;
        free(j);
        return true;
    }
    i->next = j->next;
    free(j);
    return true;
}

int getNumberOfListElements(List* list)
{
    return list->numberOfElements;
}

const char* getData(ListElement* listElement)
{
    return listElement->data;
}

int getNumberOfRepetitions(ListElement* listElement)
{
    return listElement->numbersOfRepetition;
}