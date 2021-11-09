#include <stdio.h>
#include <stdbool.h>

#include "TestsForStack.h"

int main()
{
    StackElement* head = NULL;
    bool checkOfCorrectWork = true;
    if (!areTestsPassing(&head))
    {
        printf("Tests failed");
        return -1;
    }
    deleteStack(&head, &checkOfCorrectWork);
    return 0;
}