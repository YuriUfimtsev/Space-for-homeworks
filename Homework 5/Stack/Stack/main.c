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
    if (!checkOfCorrectWork)
    {
        printf("Error with Stack deletion");
        return -1;
    }
    return 0;
}