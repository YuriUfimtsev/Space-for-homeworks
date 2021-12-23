#include <stdio.h>

#include "PriorityQueue.h"
#include "TestsForPriorityQueue.h"

int main()
{
    if (!areTestsPassing())
    {
        printf("Tests failed\n");
        return -1;
    }
    printf("Tests were successful\n");
}
