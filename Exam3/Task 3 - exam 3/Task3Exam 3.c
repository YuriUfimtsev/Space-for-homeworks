#pragma warning (disable: 4996 6031)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void deleteMatrix(int** matrix, int const matrixHeight)
{
    for (int i = 0; i < matrixHeight; ++i)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int** getMatrixFromFile(FILE* data, int* matrixHeight, int* matrixWidth)
{
    fscanf(data, "%d", matrixHeight);
    fscanf(data, "%d", matrixWidth);
    int** matrix = calloc(*matrixHeight, sizeof(int*));
    if (matrix == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < *matrixHeight; ++i)
    {
        matrix[i] = calloc(*matrixWidth, sizeof(int));
        if (matrix[i] == NULL)
        {
            deleteMatrix(matrix, i);
            return NULL;
        }
    }
    for (int i = 0; i < *matrixHeight; ++i)
    {
        for (int j = 0; j < *matrixWidth; ++j)
        {
            fscanf(data, "%d", &matrix[i][j]);
        }
    }
    return matrix;
}

int* getMatrixValue(int** matrix, const int matrixHeight, const int matrixWidth, int* sizeOfArray)
{
    *sizeOfArray = matrixHeight * matrixWidth;
    int indexForArray = 0;
    int realHeight = matrixHeight;
    int realWidth = matrixWidth;
    int* resultArray = calloc(*sizeOfArray, sizeof(int));
    if (resultArray == NULL)
    {
        return NULL;
    }
    int startIndexForHeight = 0;
    int startIndexForWidth = 0;
    while (realHeight != 0 && realWidth != 0)
    {
        for (int i = startIndexForWidth; i < realWidth; ++i)
        {
            resultArray[indexForArray] = matrix[startIndexForWidth][i];
            ++indexForArray;
            if (indexForArray >= *sizeOfArray)
            {
                break;
            }
        }
        ++startIndexForHeight;
        for (int j = startIndexForHeight; j < realHeight; ++j)
        {
            resultArray[indexForArray] = matrix[j][realWidth - 1];
            ++indexForArray;
            if (indexForArray >= *sizeOfArray)
            {
                break;
            }
        }
        --realWidth;
        for (int j = realWidth - 1; j >= startIndexForWidth; --j)
        {
            resultArray[indexForArray] = matrix[realHeight - 1][j];
            ++indexForArray;
            if (indexForArray >= *sizeOfArray)
            {
                break;
            }
        }
        --realHeight;
        for (int j = realHeight - 1; j >= startIndexForHeight; --j)
        {
            resultArray[indexForArray] = matrix[j][startIndexForWidth];
            ++indexForArray;
            if (indexForArray >= *sizeOfArray)
            {
                break;
            }
        }
        ++startIndexForWidth;
        if (indexForArray >= *sizeOfArray)
        {
            break;
        }
    }
    return resultArray;
}

bool standartTest()
{
    FILE* data = fopen("StandartTest.txt", "r");
    int matrixHeight = 0;
    int matrixWidth = 0;
    int** matrix = getMatrixFromFile(data, &matrixHeight, &matrixWidth);
    fclose(data);
    if (matrix == NULL)
    {
        return false;
    }
    int sizeOfArray = 0;
    int* array = getMatrixValue(matrix, matrixHeight, matrixWidth, &sizeOfArray);
    deleteMatrix(matrix, matrixHeight);
    if (array == NULL)
    {
        return false;
    }
    bool result = true;
    for (int i = 0; i < sizeOfArray; ++i)
    {
        if (array[i] != i + 1)
        {
            result = false;
            break;
        }
    }
    free((void*)array);
    return result;
}

bool testWithOneElementMatrix()
{
    FILE* fileWithMatrix = fopen("SpecialTest.txt", "r");
    int matrixHeight = 0;
    int matrixWidth = 0;
    int** matrix = getMatrixFromFile(fileWithMatrix, &matrixHeight, &matrixWidth);
    fclose(fileWithMatrix);
    if (matrix == NULL)
    {
        return false;
    }
    int sizeOfArray = 0;
    int* array = getMatrixValue(matrix, matrixHeight, matrixWidth, &sizeOfArray);
    deleteMatrix(matrix, matrixHeight);
    if (array == NULL)
    {
        return false;
    }
    bool const result = array[0] == 3 && sizeOfArray == 1;
    free(array);
    return result;
}


int main()
{
    if (!standartTest() || !testWithOneElementMatrix())
    {
        printf("Tests failed");
        return -1;
    }
    FILE* fileWithMatrix = fopen("matrix.txt", "r");
    int matrixHeight = 0;
    int matrixWidth = 0;
    int** matrix = getMatrixFromFile(fileWithMatrix, &matrixHeight, &matrixWidth);
    fclose(fileWithMatrix);
    if (matrix == NULL)
    {
        printf("Error with building matrix");
        return -1;
    }
    int sizeOfArray = 0;
    int* array =  getMatrixValue(matrix, matrixHeight, matrixWidth, &sizeOfArray);
    deleteMatrix(matrix, matrixHeight);
    if (array == NULL)
    {
        printf("Error with building array");
        return -1;
    }
    for (int i = 0; i < sizeOfArray; ++i)
    {
        printf("%d ", array[i]);
    }
    free(array);
}
