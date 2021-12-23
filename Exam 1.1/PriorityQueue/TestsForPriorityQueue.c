#include <stdbool.h>

#include "TestsForPriorityQueue.h"
#include "PriorityQueue.h"

bool standartTestForEnqueue()
{
    PriorityQueue* priorityQueue = createPriorityQueue();
    int resultForEnqueue = enqueue(15, 1, priorityQueue);
    resultForEnqueue = enqueue(10, 2, priorityQueue);
    int elementWithTheHighesPriority = getTopOfPriorityQueue(priorityQueue);
    bool const result = resultForEnqueue == 0 && elementWithTheHighesPriority == 10;
    deletePriorityQueue(priorityQueue);
    return result;
}

bool standartTestForDequeue()
{
    PriorityQueue* priorityQueue = createPriorityQueue();
    int resultForEnqueue = enqueue(15, 1, priorityQueue);
    resultForEnqueue = enqueue(10, 2, priorityQueue);
    resultForEnqueue = enqueue(39, 8, priorityQueue);
    resultForEnqueue = enqueue(49, 3, priorityQueue);
    resultForEnqueue = enqueue(100, -5, priorityQueue);
    int resultForDequeue = dequeue(priorityQueue);
    bool const result = resultForDequeue == 39 && resultForEnqueue == 0 && getTopOfPriorityQueue(priorityQueue) == 49;
    deletePriorityQueue(priorityQueue);
    return result;
}

bool testWithSamePriorities()
{
    PriorityQueue* priorityQueue = createPriorityQueue();
    int resultForEnqueue = enqueue(15, 1, priorityQueue);
    resultForEnqueue = enqueue(10, 1, priorityQueue);
    resultForEnqueue = enqueue(39, 1, priorityQueue);
    int const firstResultForDequeue = dequeue(priorityQueue);
    int const secondResultForDequeue = dequeue(priorityQueue);
    int const thirdResultForDequeue = dequeue(priorityQueue);
    bool const result = firstResultForDequeue == 15 && secondResultForDequeue == 10
        && thirdResultForDequeue == 39 && resultForEnqueue == 0;
    deletePriorityQueue(priorityQueue);
    return result;
}

bool testWithDequeueFromNULL()
{
    PriorityQueue* priorityQueue = createPriorityQueue();
    int const resultForDequeue = dequeue(priorityQueue);
    deletePriorityQueue(priorityQueue);
    return resultForDequeue == -1;
}

bool areTestsPassing()
{
    return standartTestForEnqueue() && standartTestForDequeue()
        && testWithSamePriorities() && testWithDequeueFromNULL();
}