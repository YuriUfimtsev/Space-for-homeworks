#pragma warning (disable: 4996)

#include "Graph.h"
#include "TestsForStates.h"

bool isStandartTestTrue(int** resultMatrix)
{
    int array[8] = { 0 };
    for (int i = 1; i < 8; ++i)
    {
        if (resultMatrix[0][i] >= 1 && resultMatrix[0][i] <= 2)
        {
            array[resultMatrix[0][i] - 1] += 1;
        }
        else if (resultMatrix[0][i] != 0)
        {
            return false;
        }
    }
    if (array[0] != 1 || array[1] != 1)
    {
        return false;
    }
    for (int i = 1; i < 8; ++i)
    {
        if (resultMatrix[1][i] >= 3 && resultMatrix[1][i] <= 8)
        {
            array[resultMatrix[1][i] - 1] += 1;
        }
        else if (resultMatrix[1][i] != 0)
        {
            return false;
        }
    }
    for (int i = 0; i < 8; ++i)
    {
        if (array[i] != 1)
        {
            return false;
        }
    }
    return true;
}

bool standartTest()
{
    FILE* data = fopen("StandartTestData.txt", "r");
    StatesAndCities* statesAndCities = getDataFromFile(data);
    fclose(data);
    buildStates(statesAndCities);
    int** resultMatrix = getResultMatrix(statesAndCities);
    const bool result = isStandartTestTrue(resultMatrix);
    deleteStatesAndCities(statesAndCities);
    return result;
}

bool isTestWithoutFreeCitiesTrue(int** resultMatrix)
{
    return resultMatrix[0][1] == 3 && resultMatrix[0][2] == 0 && resultMatrix[1][1] == 2 && resultMatrix[1][2] == 0
        && resultMatrix[2][1] == 1 && resultMatrix[2][2] == 0;
}

bool testWithoutFreeCities()
{
    FILE* data = fopen("TestWithoutFreeCitiesData.txt", "r");
    StatesAndCities* statesAndCities = getDataFromFile(data);
    fclose(data);
    buildStates(statesAndCities);
    int** resultMatrix = getResultMatrix(statesAndCities);
    const bool result = isTestWithoutFreeCitiesTrue(resultMatrix);
    deleteStatesAndCities(statesAndCities);
    return result;
}

bool areTestPassing()
{
    return standartTest() && testWithoutFreeCities();
}