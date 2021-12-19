#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"

int main()
{
    FILE* data = fopen("Data2.txt", "r");
    StatesAndCities* statesAndCities = getDataFromFile(data);
    fclose(data);
    buildStates(statesAndCities);
    printResult(statesAndCities);
    deleteStatesAndCities(statesAndCities);
}
