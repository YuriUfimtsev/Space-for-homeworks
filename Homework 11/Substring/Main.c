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
    char patternString[51] = { '\0' };
    scanf("%s", &patternString);
    FILE* data = fopen("Text.txt", "r");
    const int resultIndex = findIndexOfStringInFile(data, patternString);
    fclose(data);
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
