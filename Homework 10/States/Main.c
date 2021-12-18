#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"

int main()
{
    bool** matrix = createMatrixOfRelationsBetweenStatesAndCities(2, 8);
    printMatrix(matrix, 2, 8);
    deleteMatrix(matrix, 2);
    //Graph* graph = createGraph();
    //Node* array[6] = { NULL }; // Массив указателей
    //for (int i = 1; i <= 6; i++)
    //{
    //    array[i - 1] = addNode(graph, i);
    //}

    //setEdge(array[0], array[1], 7);
    //setEdge(array[1], array[2], 10);
    //setEdge(array[0], array[2], 9);
    //setEdge(array[0], array[5], 14);
    //setEdge(array[2], array[5], 2);
    //setEdge(array[1], array[4], 15);
    //setEdge(array[2], array[3], 11);
    //setEdge(array[3], array[4], 6);
    //setEdge(array[5], array[4], 9);

    //printf("%d", getEdge(array[0], array[1]));
    //printf("%d", getEdge(array[5], array[4]));

    //Node** visitedNodes = depthFirstSearch(graph, array[0], 6);
    //for (int i = 0; i < 6; i++)
    //{
    //    printf("%d", getData(visitedNodes[i]));
    //}
    //free(visitedNodes);
    //deleteGraph(graph);
}
