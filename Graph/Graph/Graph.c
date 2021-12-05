#include "Graph.h"

typedef struct Graph{
    Node* nodes[200];
    int nodesCount;
    int matrix[200][200];
}Graph;

typedef struct Node{
    int index;
    Graph* graph;
} Node;
