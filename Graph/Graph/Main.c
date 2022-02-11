#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"

// ����� - �� ������� ��������, ������� ����� � main. 
//������� � ������������ ����� - ����������� �������� ����� ��������
//�� ������� ����� ��������� ��� ���������. ��������� ������� ���� ����� �����������.


bool isNodeVisited(Node* node, Node* visitedNodes[], int length)
{
    for (int i = 0; i < length; ++i)
    {
        if (node = visitedNodes[i])
        {
            return true;
        }
    }
    return false;
}

void depthRecursive(Node* node, int* length, Node* result[] /* ������ ���� ������*/)
{
    result[*length] = node;
    (*length)++;
    int nearNodesCount = 0;// ���������� �������� ������
    Node** nearNodes = getNearNodes(node, &nearNodesCount);
    for (int i = 0; i < nearNodesCount; ++i)
    {
        if (!isNodeVisited(nearNodes[i], result, *length))
        {
            depthRecursive(nearNodes[i], length, result);
        }
    }
}

Node** depthFirstSearch(Graph* graph, Node* startNode, int nodesCount) // ������� � ������� �����
{
    Node** result = calloc(nodesCount, sizeof(Node*));
    int resultLength = 0;
    depthRecursive(startNode, result, &resultLength);
    return result;
}

int main(void)
{
    Graph* graph = createGraph();
    //Node* array[] = calloc(6, sizeof(Node*)); ������ ����������
    Node* array[6] = { NULL };
    for (int i = 1; i <= 6; ++i)
    {
        array[i - 1] = addNode(graph, i);
    }
    setEdge(array[0], array[1], 7);
    setEdge(array[1], array[2], 10);
    setEdge(array[0], array[2], 9);
    setEdge(array[0], array[5], 14);
    setEdge(array[2], array[5], 2);
    setEdge(array[1], array[4], 15);
    setEdge(array[2], array[3], 11);
    setEdge(array[3], array[4], 6);
    setEdge(array[5], array[4], 9);

    printf("%d ", getEdge(array[0], array[1]));
    printf("%d ", getEdge(array[3], array[4]));

    Node** visitedNodes = depthFirstSearch(graph, array[0], 6);
    for (int i = 0; i < 6; ++i)
    {
        printf("%d ", getData(visitedNodes[i]));
    }
    free(visitedNodes);
    deleteGraph(graph);
}