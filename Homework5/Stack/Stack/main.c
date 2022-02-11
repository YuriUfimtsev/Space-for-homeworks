#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "TestsForStack.h"

int main(int argc, char* argv[])
{
    if (argc == 2 && strcmp(argv[1], "tests_only") == 0)
    {
        return areTestsPassing() ? 0 : -2;
    }
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