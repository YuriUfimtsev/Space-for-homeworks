#pragma warning (disable: 6011)

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"

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

Graph* createGraph(int nodesCount)
{
    Graph* newGraph = calloc(1, sizeof(Graph));
    newGraph->nodesCount = nodesCount;
    Node** arrayOfNodes = calloc(nodesCount, sizeof(Node*));
    for (int i = 0; i < nodesCount; ++i)
    {
        arrayOfNodes[i]->value = i + 1;
        arrayOfNodes[i]->graph = newGraph;
    }
    int** adjacencyMatrix = (int**)calloc(nodesCount, sizeof(int*));
    for (int i = 0; i < nodesCount; ++i)
    {
        adjacencyMatrix[i] = (int*)calloc(nodesCount, sizeof(int));
    }
    newGraph->adjacencyMatrix = adjacencyMatrix;
    newGraph->sizeOfAdjacencyMatrix = nodesCount;
    return newGraph;
}

void deleteNode(Node* node)
{
    node->graph->arrayOfNodes[node->value - 1] = 0;
    free(node);///////////??????????????????????????????
}

void deleteGraph(Graph* graph)
{
    for (int i = 0; i < graph->nodesCount; ++i)
    {
        free(graph->adjacencyMatrix[i]);
    }
    free(graph->adjacencyMatrix);
    free(graph->arrayOfNodes);
    free(graph);
}

Node** getNearNodes(Node* node, int* nearNodesCount)
{
    const int nodeValue = node->value;
    for (int i = 0; i < node->graph->sizeOfAdjacencyMatrix; ++i)
    {
        if (node->graph->adjacencyMatrix[nodeValue - 1][i] == 1)
        {
            ++(*nearNodesCount);
        }
    }
    Node** arrayOfNearNodes = calloc(*nearNodesCount, sizeof(Node*));
    int indexOfNearNodesArray = 0;
    for (int i = 0; i < node->graph->sizeOfAdjacencyMatrix; ++i)
    {
        if (node->graph->adjacencyMatrix[nodeValue - 1][i] == 1)
        {
            arrayOfNearNodes[indexOfNearNodesArray] = node->graph->arrayOfNodes[i];
            ++indexOfNearNodesArray;
        }
    }
    return arrayOfNearNodes;
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

bool** createMatrixOfRelationsBetweenStatesAndCities(int numbersOfCities, int* arrayOfCapitalsValues,
    int lengthOfCapitalsValuesArray)
{
    int maxCapitalValue = findMaxElementOfArray(arrayOfCapitalsValues, lengthOfCapitalsValuesArray);
    bool** matrix = (bool**)calloc(maxCapitalValue, sizeof(bool*));
    for (int i = 0; i < maxCapitalValue; ++i)
    {
        matrix[i] = (bool*)calloc(numbersOfCities, sizeof(bool));
    }
    for (int i = 0; i < lengthOfCapitalsValuesArray; ++i)
    {
        matrix[arrayOfCapitalsValues[i] - 1][arrayOfCapitalsValues[i] - 1] = true;
    }
    return matrix;
}

void printMatrix(bool** matrix, int numberOfRows, int numberOfColumns)
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

void deleteMatrix(bool** matrix, int numberOfRows)
{
    for (int i = 0; i < numberOfRows; ++i)
    {
        free(matrix[i]);
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

void buildStates(Graph* graph, bool** matrixOfRelationsBetweenStatesAndCities, int* arrayOfCapitalsValues,
    int lengthOfCapitalsValuesArray)
{
    int countOfFreeCities = graph->nodesCount;
    while (countOfFreeCities > 0)
    {
        for (int i = 0; i < lengthOfCapitalsValuesArray; ++i)
        {
            if (countOfFreeCities == 0)
            {
                break;
            }
            int minDistance = 2147483647;
            int numberOfCandidateForState = 0;
            int currentCapitalNumber = arrayOfCapitalsValues[i];
            for (int j = 0; j < graph->sizeOfAdjacencyMatrix; ++j)
            {
                if (matrixOfRelationsBetweenStatesAndCities[currentCapitalNumber - 1][j])
                {
                    for (int k = 0; k < graph->sizeOfAdjacencyMatrix; ++k)
                    {
                        if (graph->adjacencyMatrix[j][k] != -1 && graph->adjacencyMatrix[j][k] < minDistance
                            && !matrixOfRelationsBetweenStatesAndCities[currentCapitalNumber - 1][k])
                        {
                            minDistance = graph->adjacencyMatrix[j][k];
                            numberOfCandidateForState = k + 1;
                        }
                    }
                }
            }
            matrixOfRelationsBetweenStatesAndCities[currentCapitalNumber - 1][numberOfCandidateForState - 1] = true;
            --countOfFreeCities;
            for (int i = 0; i < graph->sizeOfAdjacencyMatrix; ++i)
            {
                graph->adjacencyMatrix[i][numberOfCandidateForState - 1] = -1;
            }
        }
    }
}

void printResult(Graph* graph, bool** matrixOfRelationsBetweenStatesAndCities, int* arrayOfCapitalsValues,
    int lengthOfCapitalsValuesArray)
{
    int maxCapitalValue = findMaxElementOfArray(arrayOfCapitalsValues, lengthOfCapitalsValuesArray);
    int countOfStates = 0;
    for (int i = 0; i < maxCapitalValue; ++i)
    {
        if (matrixOfRelationsBetweenStatesAndCities[i][i])
        {
            ++countOfStates;
            printf("\nState number %d: ", countOfStates);
            for (int j = 0; j < graph->sizeOfAdjacencyMatrix; ++j)
            {
                if (matrixOfRelationsBetweenStatesAndCities[i][j])
                {
                    printf("%d", j + 1);
                }
            }
            printf("cities");
        }
    }
}