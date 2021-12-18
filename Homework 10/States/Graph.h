#pragma once

typedef struct Graph Graph;

typedef struct Node Node;

typedef int NodeValue;

Graph* createGraph(int nodesCount);

Node* addNode(Graph* graph, NodeValue value);

void setData(Node* node, NodeValue value);

NodeValue getData(Node* node);

void deleteGraph(Graph* graph);

Node** getNearNodes(Node* node, int* count);//////////

int getEdge(Node* firstNode, Node* secondNode);

void setEdge(Node* firstNode, Node* secondNode, int weight);

Node** depthFirstSearch(Graph* graph, Node* startNode, int nodesCount);

bool** createMatrixOfRelationsBetweenStatesAndCities(int numbersOfStates, int numbersOfCities);

void printMatrix(bool** matrix, int numberOfRows, int numberOfColumns);

void deleteMatrix(bool** matrix, int numberOfRows);

