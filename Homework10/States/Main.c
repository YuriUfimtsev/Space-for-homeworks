#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Graph.h"
#include "TestsForStates.h"

int main(int argc, char* argv[])
{
    if (argc == 2 && strcmp(argv[1], "tests_only") == 0)
    {
        return areTestPassing() ? 0 : -2;
    }
    if (!areTestPassing())
    {
        printf("Tests failed");
        return -1;
    }
    FILE* data = fopen("Homework10/States/Data.txt", "r");
    StatesAndCities* statesAndCities = getDataFromFile(data);
    fclose(data);
    buildStates(statesAndCities);
    printResult(statesAndCities);
    deleteStatesAndCities(statesAndCities);
}
