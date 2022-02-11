#pragma once

typedef struct Graph Graph;

typedef struct Node Node;

typedef int NodeValue;

//void - указание компилятору проверить, что
//createGraph вызывается без параметров
Graph* createGraph(void);

Node* addNode(Graph* graph, NodeValue value);

void deleteNode(Node* node);

void setData(Node* node, NodeValue value);

NodeValue getData(Node* node);

void deleteGraph(Graph* graph);

Node** getNearNodes(Node* node, int* length); // массив Node* ов, length - длина списка соседей

int getEdge(Node* firstNode, Node* secondNode);

void setEdge(Node* firstNode, Node* secondNode, int weight);


