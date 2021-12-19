#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"
#include "TestsForStates.h"

int main()
{
    if (!areTestPassing())
    {
        printf("Tests failed");
        return -1;
    }
    FILE* data = fopen("Data.txt", "r");
    StatesAndCities* statesAndCities = getDataFromFile(data);
    fclose(data);
    buildStates(statesAndCities);
    printResult(statesAndCities);
    deleteStatesAndCities(statesAndCities);
}
