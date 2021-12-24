#pragma warning(disable: 4996 6031)

#include <stdio.h>

#include "SubstringSearch.h"
#include "TestsForSubstringSearch.h"

int main()
{
    if (!areTestsPassing())
    {
        printf("Tests failed");
        return -1;
    }
    printf("Enter the pattern string (less than 50 symbols): ");
    char patternString[MAX_SIZE_OF_STRING] = { '\0' };
    scanf_s("%s", patternString, MAX_SIZE_OF_STRING);
    char dataFromFile[MAX_SIZE_OF_STRING] = { '\0' };
    FILE* data = fopen("Text.txt", "r");
    fscanf_s(data, "%s", dataFromFile, MAX_SIZE_OF_STRING);
    fclose(data);
    const int resultIndex = findIndexOfStringInFile(patternString, dataFromFile);
    if (resultIndex == -1)
    {
        printf("\nFile doesn't contain such number of characters\n");
    }
    else if (resultIndex == -2)
    {
        printf("\nFile doesn't contain such string\n");
    }
    else
    {
        printf("\nThe index of the beginning of this string in file = %d\n", resultIndex);
    }
}
