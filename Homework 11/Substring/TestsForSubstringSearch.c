#pragma warning(disable: 4996 6031)

#include <stdio.h>

#include "SubstringSearch.h"
#include "TestsForSubstringSearch.h"

bool standartTest()
{
    char patternString[10] = "past";
    char stringData[1000] = "";
    FILE* data = fopen("DataForStandartTest.txt", "r");
    fscanf(data, "%s", stringData);
    const int resultIndex = findIndexOfStringInFile(patternString, stringData);
    fclose(data);
    return resultIndex == 53;
}

bool testWithEmptyFile()
{
    char patternString[10] = "SGU";
    char stringData[1000] = "";
    FILE* data = fopen("EmptyFileForTest.txt", "r");
    fscanf(data, "%s", stringData);
    const int resultIndex = findIndexOfStringInFile(patternString, stringData);
    fclose(data);
    return resultIndex == -1;
}

bool testWithSmallString()
{
    char patternString[10] = "SPBU";
    char stringData[1000] = "";
    FILE* data = fopen("DataForTestWithSmallString.txt", "r");
    fscanf(data, "%s", stringData);
    const int resultIndex = findIndexOfStringInFile(patternString, stringData);
    fclose(data);
    return resultIndex == -1;
}

bool areTestsPassing()
{
    return standartTest() && testWithEmptyFile() && testWithSmallString();
}