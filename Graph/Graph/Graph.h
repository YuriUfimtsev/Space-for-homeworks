#pragma once

typedef struct Graph Graph;

typedef struct Node Node;

typedef int NodeValue;

//void - �������� ����������� ���������, ���
//createGraph ���������� ��� ����������
Graph* createGraph(void);

Node* addNode(Graph* graph, NodeValue value);

void deleteNode(Node* node);

void setData(Node* node, NodeValue value);

NodeValue getData(Node* node);

void deleteGraph(Graph* graph);

Node** getNearNodes(Node* node, int* length); // ������ Node* ��, length - ����� ������ �������

int getEdge(Node* firstNode, Node* secondNode);

void setEdge(Node* firstNode, Node* secondNode, int weight);


