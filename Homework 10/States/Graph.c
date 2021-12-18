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

bool nodeIsVisited(Node* node, Node* visitedNodes[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (node == visitedNodes[i])
        {
            return true;
        }
    }
    return false;
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

void depthRecursive(Node* node, Node* result[], int* length)
{
    result[*length] = node;
    (*length)++;
    int nearNodesCount = 0;
    Node** nearNodes = getNearNodes(node, &nearNodesCount);
    for (int i = 0; i < nearNodesCount; i++)
    {
        if (!nodeIsVisited(nearNodes[i], result, *length))
        {
            depthRecursive(nearNodes[i], result, length);
        }
    }
}

Node** depthFirstSearch(Graph* graph, Node* startNode, int nodesCount)
{
    Node** result = calloc(nodesCount, sizeof(Node*));
    int resultLength = 0;
    depthRecursive(startNode, result, &resultLength);
    return result;
}

bool** createMatrixOfRelationsBetweenStatesAndCities(int numbersOfStates, int numbersOfCities)
{
    bool** matrix = (bool**)calloc(numbersOfStates, sizeof(bool*));
    for (int i = 0; i < numbersOfStates; ++i)
    {
        matrix[i] = (bool*)calloc(numbersOfCities, sizeof(bool));
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