#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void dfs(int node, int* nodes[], int matrix[][5])
{
     nodes[node] = node;
    for (int i = 0; i <= 5; ++i)
    {
        for (int j = 0; j <= 5; ++j)
        {
            if (matrix[i][j] == 1 && i != j)
            {
                if (nodes[j] != j)
                {
                    dfs(j, nodes, matrix);
                    nodes[j] = i;
                }
            }
        }
    }
}

int main()
{
    int matrix[5][5] = { { 0, 1, 1, 0, 0 }, // матрица инцидентности
/*    { 1, 0, 1, 1, 0 },
    { 1, 1, 0, 0, 0 },
    { 0, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 0 }*/
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 0 }
    };
    int nodes[5] = { 0 };
    int arrayOfConnectiveComponents[5] = {0};
    for (int i = 0; i < 5; ++i)
    {
        dfs(i, &nodes, matrix);
    }
    for (int i = 0; i < 5; ++i)
    {
        ++arrayOfConnectiveComponents[nodes[i]];
    }
    for (int i = 0; i < 5; ++i)
    {
        if (arrayOfConnectiveComponents[i] != 0)
        {
            printf("\n%d    ", i + 1);
            for (int j = 0; j < 5; ++j)
            {
                if (nodes[j] == i && j != i)
                {
                    printf("%d ", j + 1);
                }
            }
        }
    }

}
