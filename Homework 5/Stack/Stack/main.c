#include <stdio.h>
#include <stdbool.h>

#include "TestsForStack.h"

int main()
{
    StackElement* head = NULL;
    if (!areTestsPassing(&head))
    {
        printf("Tests failed");
        return -1;
    }
    return 0;
}