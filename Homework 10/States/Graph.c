#pragma warning (disable: 4996 6011 6031)

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"

typedef struct StatesAndCities
{
    Graph* graph;
    int* arrayOfCapitals;
    int sizeOfArrayOfCapitals;
    bool** matrixOfRelationsBetweenStatesAndCities;
    int** resultStatesMatrix;
} StatesAndCities;

typedef struct Graph
{
    Node** arrayOfNodes;
    int nodesCount;
    int** adjacencyMatrix;
    int sizeOfAdjacencyMatrix;
} Graph;

typedef struct Node
{
    int value;
    Graph* graph;
} Node;

bool** getBoolTypeMatrix(StatesAndCities* statesAndCities)
{
    return statesAndCities->matrixOfRelationsBetweenStatesAndCities;
}

int** getIntTypeMatrix(StatesAndCities* statesAndCities)
{
    return statesAndCities->resultStatesMatrix;
}

Graph* createGraph(int nodesCount)
{
    Graph* newGraph = calloc(1, sizeof(Graph));
    newGraph->nodesCount = nodesCount;
    Node** arrayOfNodes = calloc(nodesCount, sizeof(Node*));
    for (int i = 0; i < nodesCount; ++i)
    {
        arrayOfNodes[i] = calloc(1, sizeof(Node));
        arrayOfNodes[i]->value = i + 1;
        arrayOfNodes[i]->graph = newGraph;
    }
    int** adjacencyMatrix = (int**)calloc(nodesCount, sizeof(int*));
    for (int i = 0; i < nodesCount; ++i)
    {
        adjacencyMatrix[i] = (int*)calloc(nodesCount, sizeof(int));
    }
    newGraph->arrayOfNodes = arrayOfNodes;
    newGraph->adjacencyMatrix = adjacencyMatrix;
    newGraph->sizeOfAdjacencyMatrix = nodesCount;
    return newGraph;
}

StatesAndCities* createStatesAndCities()
{
    return calloc(1, sizeof(StatesAndCities));
}

void deleteGraph(Graph* graph)
{
    for (int i = 0; i < graph->sizeOfAdjacencyMatrix; ++i)
    {
        free(graph->adjacencyMatrix[i]);
    }
    for (int i = 0; i < graph->nodesCount; ++i)
    {
        free(graph->arrayOfNodes[i]);
    }
    free(graph->adjacencyMatrix);
    free(graph->arrayOfNodes);
    free(graph);
}

int findMaxElementOfArray(int* array, int lengthOfArray)
{
    int result = 0;
    for (int i = 0; i < lengthOfArray; ++i)
    {
        if (array[i] > result)
        {
            result = array[i];
        }
    }
    return result;
}

bool** createMatrixOfRelationsBetweenStatesAndCities(StatesAndCities* statesAndCities)
{
    int maxCapitalValue = findMaxElementOfArray(statesAndCities->arrayOfCapitals, statesAndCities->sizeOfArrayOfCapitals);
    bool** matrix = (bool**)calloc(maxCapitalValue, sizeof(bool*));
    for (int i = 0; i < maxCapitalValue; ++i)
    {
        matrix[i] = (bool*)calloc(statesAndCities->graph->sizeOfAdjacencyMatrix, sizeof(bool));
    }
    for (int i = 0; i < statesAndCities->sizeOfArrayOfCapitals; ++i)
    {
        matrix[statesAndCities->arrayOfCapitals[i] - 1][statesAndCities->arrayOfCapitals[i] - 1] = true;
    }
    return matrix;
}

void createResultStatesMatrix(StatesAndCities* statesAndCities)
{
    int** resultMatrix = (int**)calloc(statesAndCities->sizeOfArrayOfCapitals, sizeof(int*));
    for (int i = 0; i < statesAndCities->sizeOfArrayOfCapitals; ++i)
    {
        resultMatrix[i] = (int*)calloc(statesAndCities->graph->sizeOfAdjacencyMatrix + 1, sizeof(int));
        resultMatrix[i][0] = i + 1;
    }
    //printBoolTypeMatrix(statesAndCities->matrixOfRelationsBetweenStatesAndCities, 4, 8);/////
    for (int i = 0; i < statesAndCities->sizeOfArrayOfCapitals; ++i)
    {
        resultMatrix[i][1] = statesAndCities->arrayOfCapitals[i];
        int indexForResultMatrixRow = 2;
        for (int j = 0; j < statesAndCities->graph->sizeOfAdjacencyMatrix; ++j)
        {
            if (statesAndCities->matrixOfRelationsBetweenStatesAndCities[statesAndCities->arrayOfCapitals[i] - 1][j]
                && statesAndCities->arrayOfCapitals[i] - 1 != j)
            {
                resultMatrix[i][indexForResultMatrixRow] = j + 1;
                ++indexForResultMatrixRow;
            }
        }
    }
    statesAndCities->resultStatesMatrix = resultMatrix;
}

void printResult(StatesAndCities* statesAndCities)
{
    for (int i = 0; i < statesAndCities->sizeOfArrayOfCapitals; ++i)
    {
        printf("\nState number %d: ", statesAndCities->resultStatesMatrix[i][0]);
        printf("capital %d and cities", statesAndCities->resultStatesMatrix[i][1]);
        int indexOfResultMatrixRow = 2;
        while (indexOfResultMatrixRow < statesAndCities->graph->sizeOfAdjacencyMatrix
            && statesAndCities->resultStatesMatrix[i][indexOfResultMatrixRow] != 0)
        {
            printf(" %d", statesAndCities->resultStatesMatrix[i][indexOfResultMatrixRow]);
            ++indexOfResultMatrixRow;
        }
        if (indexOfResultMatrixRow == 2)
        {
            printf(" null");
        }
        printf(".");
    }
}

//void printResult(StatesAndCities* statesAndCities)
//{
//    int maxCapitalValue = findMaxElementOfArray(statesAndCities->arrayOfCapitals, statesAndCities->sizeOfArrayOfCapitals);
//    int countOfStates = 0;
//    for (int i = 0; i < maxCapitalValue; ++i)
//    {
//        if (statesAndCities->matrixOfRelationsBetweenStatesAndCities[i][i])
//        {
//            ++countOfStates;
//            printf("\nState number %d: ", countOfStates);
//            printf("%d capital and ", i + 1);
//            for (int j = 0; j < statesAndCities->graph->sizeOfAdjacencyMatrix; ++j)
//            {
//                if (statesAndCities->matrixOfRelationsBetweenStatesAndCities[i][j] && i != j)
//                {
//                    printf("%d ", j + 1);
//                }
//            }
//            printf("cities");
//        }
//    }
//}

void deleteIntTypeMatrix(int** matrix, int numberOfRows)
{
    for (int i = 0; i < numberOfRows; ++i)
    {
        free((void*)matrix[i]);
    }
    free(matrix);
}

void printBoolTypeMatrix(bool** matrix, int numberOfRows, int numberOfColumns)
{
    for (int i = 0; i < numberOfRows; ++i)
    {
        for (int j = 0; j < numberOfColumns; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printIntTypeMatrix(int** matrix, int numberOfRows, int numberOfColumns)
{
    for (int i = 0; i < numberOfRows; ++i)
    {
        for (int j = 0; j < numberOfColumns; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void deleteBoolTypeMatrix(bool** matrix, int numberOfRows)
{
    for (int i = 0; i < numberOfRows; ++i)
    {
        free((void*)matrix[i]);
    }
    free(matrix);
}

void setEdgeWithNodes(Node* firstNode, Node* secondNode, int distance)
{
    firstNode->graph->adjacencyMatrix[firstNode->value - 1][secondNode->value - 1] = distance;
    firstNode->graph->adjacencyMatrix[secondNode->value - 1][firstNode->value - 1] = distance;
}

void setEdgeWithNodesValues(int firstNodeValue, int secondNodeValue, int distance, Graph* graph)
{
    graph->adjacencyMatrix[firstNodeValue - 1][secondNodeValue - 1] = distance;
    graph->adjacencyMatrix[secondNodeValue - 1][firstNodeValue - 1] = distance;
}

StatesAndCities* getDataFromFile(FILE* data)
{
    int nodesCount = 0;
    fscanf(data, "%d", &nodesCount);
    Graph* graphOfCities = createGraph(nodesCount);
    int edgesCount = 0;
    fscanf(data, "%d", &edgesCount);
    for (int i = 0; i < edgesCount; ++i)
    {
        int firstNodeValue = 0;
        fscanf(data, "%d", &firstNodeValue);
        int secondNodeValue = 0;
        fscanf(data, "%d", &secondNodeValue);
        int edgeValue = 0;
        fscanf(data, "%d", &edgeValue);
        setEdgeWithNodesValues(firstNodeValue, secondNodeValue, edgeValue, graphOfCities);
    }
    StatesAndCities* statesAndCities = createStatesAndCities();
    statesAndCities->graph = graphOfCities;
    int sizeOfArrayOfCapitals = 0;
    fscanf(data, "%d", &sizeOfArrayOfCapitals);
    int* arrayOfCapitals = calloc(sizeOfArrayOfCapitals, sizeof(int));
    for (int i = 0; i < sizeOfArrayOfCapitals; ++i)
    {
        int capitalNumber = 0;
        fscanf(data, "%d", &capitalNumber);
        arrayOfCapitals[i] = capitalNumber;
    }
    statesAndCities->arrayOfCapitals = arrayOfCapitals;
    statesAndCities->sizeOfArrayOfCapitals = sizeOfArrayOfCapitals;
    bool** matrixOfRelationsBetweenStatesAndCities = createMatrixOfRelationsBetweenStatesAndCities(statesAndCities);
    statesAndCities->matrixOfRelationsBetweenStatesAndCities = matrixOfRelationsBetweenStatesAndCities;
    return statesAndCities;
}

void buildStates(StatesAndCities* statesAndCities)
{
    for (int i = 0; i < statesAndCities->sizeOfArrayOfCapitals; ++i)
    {
        for (int j = 0; j < statesAndCities->graph->sizeOfAdjacencyMatrix; ++j)
        {
            statesAndCities->graph->adjacencyMatrix[j][statesAndCities->arrayOfCapitals[i] - 1] = -1;
        }
    }
    int countOfFreeCities = statesAndCities->graph->nodesCount - statesAndCities->sizeOfArrayOfCapitals;
    while (countOfFreeCities > 0)
    {
        for (int i = 0; i < statesAndCities->sizeOfArrayOfCapitals; ++i)
        {
            if (countOfFreeCities == 0)
            {
                break;
            }
            int minDistance = INT_MAX;
            int numberOfCandidateForState = 0;
            int currentCapitalNumber = statesAndCities->arrayOfCapitals[i];
            for (int j = 0; j < statesAndCities->graph->sizeOfAdjacencyMatrix; ++j)
            {
                if (statesAndCities->matrixOfRelationsBetweenStatesAndCities[currentCapitalNumber - 1][j])
                {
                    for (int k = 0; k < statesAndCities->graph->sizeOfAdjacencyMatrix; ++k)
                    {
                        if (statesAndCities->graph->adjacencyMatrix[j][k] > 0
                            && statesAndCities->graph->adjacencyMatrix[j][k] <= minDistance
                            && !statesAndCities->matrixOfRelationsBetweenStatesAndCities[currentCapitalNumber - 1][k])
                        {
                            minDistance = statesAndCities->graph->adjacencyMatrix[j][k];
                            numberOfCandidateForState = k + 1;
                        }
                    }
                }
            }
            if (numberOfCandidateForState != 0)
            {
                statesAndCities->matrixOfRelationsBetweenStatesAndCities[currentCapitalNumber - 1]
                    [numberOfCandidateForState - 1] = true;
                --countOfFreeCities;
                for (int i = 0; i < statesAndCities->graph->sizeOfAdjacencyMatrix; ++i)
                {
                    statesAndCities->graph->adjacencyMatrix[i][numberOfCandidateForState - 1] = -1;
                }
            }
        }
    }
    createResultStatesMatrix(statesAndCities);
}

void deleteStatesAndCities(StatesAndCities* statesAndCities)
{
    int rowsInBoolTypeMatrix = findMaxElementOfArray(statesAndCities->arrayOfCapitals,
        statesAndCities->sizeOfArrayOfCapitals);
    deleteBoolTypeMatrix(statesAndCities->matrixOfRelationsBetweenStatesAndCities, rowsInBoolTypeMatrix);
    deleteIntTypeMatrix(statesAndCities->resultStatesMatrix, statesAndCities->sizeOfArrayOfCapitals);
    deleteGraph(statesAndCities->graph);
    free(statesAndCities->arrayOfCapitals);
    free(statesAndCities);
}