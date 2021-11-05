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
    return  (List*)calloc(1, sizeof(List));
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
    ListElement* newElement = (ListElement*)calloc(1, sizeof(ListElement));
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

int getValue(List* list, Position* position)
{
    return position->position->value;
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

void addTheValueInSortedList(List* list, int value)
{
    ListElement* newElement = (ListElement*)calloc(1, sizeof(ListElement));
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

int sizeOfList(List* list)
{
    int counter = 0;
    for (Position* i = first(list); !last(i); i = next(i))
    {
        getValue(list, i);
        ++counter;
    }
    return counter + 1;
}

//List* divideList(List* list)
//{
//    int const size = sizeOfList(list);
//    if (size > 1)
//    {
//        Position* i = first(list);
//        for (int j = 0; j < size / 2; ++j)
//        {
//            i = next(i);
//        }
//        List* halfOfList = createList();
//        halfOfList->head = i->position->next;
//        i->position->next = NULL;
//        divideList(list);
//        divideList(halfOfList);
//
//    }
//    else if (size == 1)
//    {
//        return list;
//    }
//}
