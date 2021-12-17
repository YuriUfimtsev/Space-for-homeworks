#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "List.h"

typedef struct ListElement
{
    int numberOfRepetitions;
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
        free((void*)position->data);
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

bool addTheDataInList(List* list, int numberOfRepetitions, const char* data)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return false;
    }
    newElement->numberOfRepetitions = numberOfRepetitions;
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
        if (strcmp(data, currentElement->data) == 0)
        {
            currentElement->numberOfRepetitions += numberOfRepetitions;
            free((void*)data);
            free(newElement);
            return false;
        }
        currentElement = currentElement->next;
    }
    if (strcmp(data, currentElement->data) == 0)
    {
        currentElement->numberOfRepetitions += numberOfRepetitions;
        free((void*)data);
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
        free((void*)i->data);
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

const char* getData(Position* position)
{
    return position->position->data;
}

int getNumberOfRepetitionsByPosition(Position* position)
{
    return position->position->numberOfRepetitions;
}

int getNumberOfRepetitionsByHash(const char* data, List* list)
{
    if (list->numberOfElements == 0)
    {
        return 0;
    }
    ListElement* i = list->head;
    while (i != NULL)
    {
        if (strcmp(i->data, data) == 0)
        {
            return i->numberOfRepetitions;
        }
        i = i->next;
    }
    free(i);
    return 0;
}
