#pragma warning (disable: 4996 6031)

#define MATRIX_HEIGHT 4
#define MATRIX_WIDTH 4
#define MAX_SIZE_OF_STRING 20

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

enum States
{
    startState = 0,
    seenSlash = 1,
    seenFirstStar = 2,
    seenSecondStar = 3
} States;


bool isNewSymbol(char newSymbol)
{
    return newSymbol != '/' && newSymbol != '*';
}

void deleteMatrix(char*** matrix, const int matrixHeight, const int matrixWidth, const bool isDeleteStrings)
{
    for (int i = 0; i < MATRIX_HEIGHT; ++i)
    {
        if (isDeleteStrings)
        {
            for (int j = 0; j < matrixWidth; ++j)
            {
                free(matrix[i][j]);
            }
        }
        free(matrix[i]);
    }
    free(matrix);
}

char*** getMatrixOfConditionsFromFile(FILE* data)
{
    char*** matrixOfConditions = calloc(MATRIX_HEIGHT, sizeof(char**));
    if (matrixOfConditions == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < MATRIX_HEIGHT; ++i)
    {
        matrixOfConditions[i] = calloc(MAX_SIZE_OF_STRING, sizeof(char*));
        if (matrixOfConditions[i] == NULL)
        {
            deleteMatrix(matrixOfConditions, i, i, false);
            return NULL;
        }
    }
    for (int i = 0; i < MATRIX_HEIGHT; ++i)
    {
        for (int j = 0; j < MATRIX_WIDTH; ++j)
        {
            char* buffer = calloc(MAX_SIZE_OF_STRING, sizeof(char));
            fscanf(data, "%s", buffer);
            matrixOfConditions[i][j] = buffer;

        }
    }
    return matrixOfConditions;
}

void printfCharMatrix(char*** matrix)
{
    for (int i = 0; i < MATRIX_HEIGHT; ++i)
    {
        for (int j = 0; j < MATRIX_WIDTH; ++j)
        {
            printf("%s ", matrix[i][j]);
        }
        printf("\n");
    }
}

char** arrayOfComments(FILE* data)
{
    char* comment[MAX_SIZE_OF_STRING] = { '\0' };
    enum States state = 0;
    char buffer = ' ';
    while (fscanf(data, "%c", buffer) > 0)
    {
        while (startState != )
    }
}

int main()
{
    FILE* data = fopen("TableOfConditions.txt", "r");
    char*** matrixOfConditions = getMatrixOfConditionsFromFile(data);
    printfCharMatrix(matrixOfConditions);
    fclose(data);

}
