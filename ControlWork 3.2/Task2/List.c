#pragma warning (disable: 4996)

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "List.h"

#define MODULE_FOR_HASH 113
#define SIMPLE_NUMBER_FOR_HASH 19

typedef struct ListElement
{
    const char* value;
    int hash;
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

const char* dataToInsert(const char* data)
{
    char* dataForHashTable = malloc(30);
    if (dataForHashTable == NULL)
    {
        return NULL;
    }
    strcpy_s(dataForHashTable, 30, data);
    return dataForHashTable;
}

int calculateHashFunction(const char* word)
{
    int result = 0;
    unsigned int wordLength = (unsigned int)strlen(word);
    int numberForHashFunctionInDegree = 1;
    for (unsigned int i = 0; i < wordLength; ++i)
    {
        result += word[i] * numberForHashFunctionInDegree;
        numberForHashFunctionInDegree *= SIMPLE_NUMBER_FOR_HASH;
    }
    return result % MODULE_FOR_HASH;
}

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
        free((void*)position->value);
        free(position);
        position = list->head;
    }
    free(list);
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

const char* getValue(List* list, Position* position)
{
    if (position->position == NULL)
    {
        return NULL;
    }
    return position->position->value;
}

int addTheValueInList(List* list, const char* value)
{
    const int currentHash = calculateHashFunction(value);
    ListElement* newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return -1;
    }
    newElement->value = dataToInsert(value);
    newElement->hash = currentHash;
    if (list->head == NULL)
    {
        list->head = newElement;
        return 0;
    }
    ListElement* i = list->head;
    while (i->next != NULL)
    {
        if (currentHash == i->hash)
        {
            if (strcmp(value, i->value) == 0)
            {
                free((void*)newElement->value);
                free(newElement);
                return 1;
            }
        }
        i = i->next;
    }
    if (currentHash == i->hash)
    {
        if (strcmp(value, i->value) == 0)
        {
            free((void*)newElement->value);
            free(newElement);
            return 1;
        }
    }
    i->next = newElement;
    return 0;
}

void printListElements(List* list)
{
    if (list->head == NULL)
    {
        return;
    }
    ListElement* i = list->head;
    while (i != NULL)
    {
        printf("\n%s", i->value);
        i = i->next;
    }
}

List* fillListFromFile(FILE* data)
{
    List* listOfStrings = createList();
    char string[50] = { '\0' };
    int resultForAddingInList = 0;
    while (fscanf(data, "%s", &string) > 0)
    {
        resultForAddingInList = addTheValueInList(listOfStrings, string);
        if (resultForAddingInList == -1)
        {
            deleteList(listOfStrings);
            return NULL;
        }
    }
    return listOfStrings;
}
