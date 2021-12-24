#pragma warning (disable: 4996)

#define MAX_SIZE_OF_ARRAY 100
#define MAX_SIZE_OF_STRING 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void deleteArray(const char** array, const int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; ++i)
    {
        free((void*)array[i]);
    }
    free((void*)array);
}

char** makeArrayFromFile(FILE* data, int* sizeOfArray)
{
    char buffer[50] = { '\0' };
    char** array = calloc(MAX_SIZE_OF_ARRAY, sizeof(char*));
    if (array == NULL)
    {
        return NULL;
    }
    while (fscanf(data, "%s", buffer) > 0)
    {
        bool isInArray = false;
        for (int i = 0; i < (*sizeOfArray); ++i)
        {
            if (strcmp(array[i], buffer) == 0)
            {
                isInArray = true;
                break;
            }
        }
        if (!isInArray)
        {
            char* newString = calloc(50, sizeof(char));
            if (newString == NULL)
            {
                deleteArray(array, *sizeOfArray);
                return NULL;
            }
            strcpy(newString, buffer);
            array[*sizeOfArray] = newString;
            ++(*sizeOfArray);
        }
    }
    return array;
}

void bubbleSort(char** array, const int lengthOfArray)
{
    for (int i = 1; i < lengthOfArray; ++i)
    {
        bool isSorting = false;
        for (int j = 0; j < lengthOfArray - i; ++j)
        {
            if (strcmp(array[j], array[j + 1]) > 0)
            {
                char buffer[MAX_SIZE_OF_STRING] = { '\0' };
                strcpy_s(buffer, MAX_SIZE_OF_STRING, array[j]);
                strcpy_s(array[j], MAX_SIZE_OF_STRING, array[j + 1]);
                strcpy_s(array[j + 1], MAX_SIZE_OF_STRING, buffer);
                isSorting = true;
            }
        }
        if (!isSorting)
        {
            break;
        }
    }
}

void fillFileFromArray(const char** array, const int lengthOfArray, FILE* resultFile)
{
    for (int i = 0; i < lengthOfArray; ++i)
    {
        fprintf(resultFile, "%s ", array[i]);
    }
}

bool standartTest()
{
    FILE* data = fopen("FileForStandartTest.txt", "r");
    int sizeOfArray = 0;
    char** array = makeArrayFromFile(data, &sizeOfArray);
    if (array == NULL)
    {
        return false;
    }
    fclose(data);
    bubbleSort(array, sizeOfArray);
    bool const result = strcmp(array[0], "000") == 0 && strcmp(array[1], "111") == 0
        && strcmp(array[2], "222") == 0 && sizeOfArray == 3;
    deleteArray(array, sizeOfArray);
    return result;
}

bool testWithEmptyFile()
{
    FILE* data = fopen("EmptyFile.txt", "r");
    int sizeOfArray = 0;
    char** array = makeArrayFromFile(data, &sizeOfArray);
    if (array == NULL)
    {
        return false;
    }
    fclose(data);
    bubbleSort(array, sizeOfArray);
    bool const result = sizeOfArray == 0;
    deleteArray(array, sizeOfArray);
    return result;
}

int main()
{
    if (!standartTest() || !testWithEmptyFile())
    {
        printf("Tests failed");
        return -1;
    }
    int sizeOfArray = 0;
    FILE* data = fopen("Data.txt", "r");
    char** array = makeArrayFromFile(data, &sizeOfArray);
    if (array == NULL)
    {
        printf("Error with array making");
        return -1;
    }
    fclose(data);
    bubbleSort(array, sizeOfArray);
    FILE* fileForWriting = fopen("ResultFile.txt", "w+");
    fillFileFromArray(array, sizeOfArray, fileForWriting);
    deleteArray(array, sizeOfArray);
    fclose(fileForWriting);
}