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
        ///free((void*)position->data);////
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

bool addTheValueInList(List* list, int value, const char* data)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return false;
    }
    newElement->numbersOfRepetition = value;
    newElement->data = data;
    if (list->head == NULL)
    {
        list->head = newElement;
        ++list->numberOfElements;
        return true;
    }
    ListElement* currentElement = list->head;
    while (currentElement->next != NULL)
    {
        if (data == currentElement->data)
        {
            currentElement->numbersOfRepetition += value;
            //////////////////free(data);//////////??????????????7
            free(newElement);
            return false;
        }
        currentElement = currentElement->next;
    }
    if (data == currentElement->data)
    {
        currentElement->numbersOfRepetition += value;
        //////////////////free(data);//////////??????????????7
        free(newElement);
        return false;
    }
    currentElement->next = newElement;
    ++list->numberOfElements;
    return true;
}

bool delete(List* list, const char* data)
{
    if (list->numberOfElements == 0)
    {
        return false;
    }
    ListElement* i = list->head;
    if (i->data == data)
    {
        list->head = i->next;
        //free((void*)i->data);////
        free(i);
        --list->numberOfElements;
        return true;
    }
    ListElement* j = list->head->next;
    while (j != NULL && j->data != data)
    {
        i = i->next;
        j = j->next;
    }
    if (j == NULL)
    {
        return false;
    }
    i->next = j->next;
    free((void*)j->data);
    free(j);
    --list->numberOfElements;
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