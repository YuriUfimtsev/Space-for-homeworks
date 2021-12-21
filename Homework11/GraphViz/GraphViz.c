#pragma warning (disable: 4996 6031)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int** getAdjacencyMatrixFromFile(FILE* data, int* matrixHeight, int* matrixWidth)
{
    fscanf(data, "%d", matrixHeight);
    fscanf(data, "%d", matrixWidth);
    int** adjacencyMatrix = calloc(*matrixHeight, sizeof(int*));
    if (adjacencyMatrix == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < *matrixHeight; ++i)
    {
        adjacencyMatrix[i] = calloc(*matrixWidth, sizeof(int));
        if (adjacencyMatrix[i] == NULL)
        {
            return NULL;
        }
    }
    for (int i = 0; i < *matrixHeight; ++i)
    {
        for (int j = 0; j < *matrixWidth; ++j)
        {
            fscanf(data, "%d", &adjacencyMatrix[i][j]);
        }
    }
    return adjacencyMatrix;
}

void deleteMatrix(int** matrix, int const matrixHeight)
{
    for (int i = 0; i < matrixHeight; ++i)
    {
        free(matrix[i]);
    }
    free(matrix);
}

FILE* makeDotFile(int** adjacencyMatrix, const int matrixHeight, const int matrixWidth)
{
    FILE* dotFile = fopen("FileForGraphViz.dot", "w");
    fprintf(dotFile, "%s", "graph GoodGraph { \n");
    for (int i = 0; i < matrixHeight; ++i)
    {
        for (int j = i; j < matrixWidth; ++j)
        {
            if (adjacencyMatrix[i][j] == 1)
            {
                fprintf(dotFile, "%s", "    ");
                fprintf(dotFile, "%d", i + 1);
                fprintf(dotFile, "%s", " -- ");
                fprintf(dotFile, "%d", j + 1);
                fprintf(dotFile, "%s", ";\n");
            }
        }
    }
    fprintf(dotFile, "%c", '}');
    fclose(dotFile);
    return dotFile;
}

int main()
{
    FILE* fileWithAdjacencyMatrix = fopen("AdjacencyMatrix.txt", "r");
    int matrixHeight = 0;
    int matrixWidth = 0;
    int** adjacencyMatrix = getAdjacencyMatrixFromFile(fileWithAdjacencyMatrix, &matrixHeight, &matrixWidth);
    if (adjacencyMatrix == NULL)
    {
        fclose(fileWithAdjacencyMatrix);
        printf("Error with calloc");
        return -1;
    }
    fclose(fileWithAdjacencyMatrix);
    FILE* fileForGraphViz = makeDotFile(adjacencyMatrix, matrixHeight, matrixWidth);
    const char* string = getenv("GraphViz");
    system("dot FileForGraphViz.dot -Tpng -o SpectacularGraph.png");
    system(".\\SpectacularGraph.png");
    deleteMatrix(adjacencyMatrix, matrixHeight);
}
