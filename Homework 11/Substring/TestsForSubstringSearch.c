#pragma warning(disable: 4996)

#include <stdio.h>

#include "SubstringSearch.h"
#include "TestsForSubstringSearch.h"

bool standartTest()
{
    char patternString[MAX_SIZE_OF_STRING] = "past";
    FILE* data = fopen("DataForStandartTest.txt", "r");
    char buffer[MAX_SIZE_OF_STRING] = { '\0' };
    fscanf_s(data, "%s", buffer, MAX_SIZE_OF_STRING);
    fclose(data);
    const int resultIndex = findIndexOfStringInFile(patternString, buffer);
    return resultIndex == 53;
}

bool testWithEmptyFile()
{
    char patternString[10] = "SGU";
    FILE* data = fopen("EmptyFileForTest.txt", "r");
    char buffer[MAX_SIZE_OF_STRING] = { '\0' };
    fscanf_s(data, "%s", buffer, MAX_SIZE_OF_STRING);
    fclose(data);
    const int resultIndex = findIndexOfStringInFile(patternString, buffer);
    return resultIndex == -1;
}

bool testWithSmallString()
{
    char patternString[10] = "SPBU";
    FILE* data = fopen("DataForTestWithSmallString.txt", "r");
    char buffer[MAX_SIZE_OF_STRING] = { '\0' };
    fscanf_s(data, "%s", buffer, MAX_SIZE_OF_STRING);
    fclose(data);
    const int resultIndex = findIndexOfStringInFile(patternString, buffer);
    return resultIndex == -1;
}

bool areTestsPassing()
{
    return standartTest() && testWithEmptyFile() && testWithSmallString();
}