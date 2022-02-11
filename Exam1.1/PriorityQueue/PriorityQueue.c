#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "PriorityQueue.h"

typedef struct PriorityQueue
{
    PriorityQueueElement* head;
} PriorityQueue;

typedef struct PriorityQueueElement
{
    int value;
    int priority;
    struct PriorityQueueElement* next;
} PriorityQueueElement;

PriorityQueue* createPriorityQueue()
{
    return calloc(1, sizeof(PriorityQueue));
}

int enqueue(const int value, const int priority, PriorityQueue* priorityQueue)
{
    PriorityQueueElement* newElement = calloc(1, sizeof(PriorityQueueElement));
    if (newElement == NULL)
    {
        return -1;
    }
    newElement->value = value;
    newElement->priority = priority;
    if (priorityQueue->head == NULL)
    {
        priorityQueue->head = newElement;
        return 0;
    }
    if (priority > priorityQueue->head->priority)
    {
        newElement->next = priorityQueue->head;
        priorityQueue->head = newElement;
        return 0;
    }
    PriorityQueueElement* i = priorityQueue->head;
    while (i->next != NULL && priority <= i->next->priority)
    {
        i = i->next;
    }
    if (i->next == NULL)
    {
        i->next = newElement;
        return 0;
    }
    newElement->next = i->next;
    i->next = newElement;
    return 0;
}

int dequeue(PriorityQueue* priorityQueue)
{
    if (priorityQueue->head == NULL)
    {
        return -1;
    }
    PriorityQueueElement* elementToRemove = priorityQueue->head;
    priorityQueue->head = priorityQueue->head->next;
    const int resultElement = elementToRemove->value;
    free(elementToRemove);
    return resultElement;
}

void deletePriorityQueue(PriorityQueue* priorityQueue)
{
    while (priorityQueue->head != NULL)
    {
        PriorityQueueElement* elementToRemove = priorityQueue->head;
        priorityQueue->head = priorityQueue->head->next;
        free(elementToRemove);
    }
}

int getTopOfPriorityQueue(PriorityQueue* priorityQueue)
{
    if (priorityQueue->head == NULL)
    {
        return -1;
    }
    return priorityQueue->head->value;
}

