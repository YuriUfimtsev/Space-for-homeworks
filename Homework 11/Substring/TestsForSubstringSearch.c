#pragma warning(disable: 4996)

#include <stdio.h>

#include "SubstringSearch.h"
#include "TestsForSubstringSearch.h"

bool standartTest()
{
    char patternString[10] = "past";
    FILE* data = fopen("DataForStandartTest.txt", "r");
    const int resultIndex = findIndexOfStringInFile(data, patternString);
    fclose(data);
    return resultIndex == 63;
}

bool testWithEmptyFile()
{
    char patternString[10] = "SGU";
    FILE* data = fopen("EmptyFileForTest.txt", "r");
    const int resultIndex = findIndexOfStringInFile(data, patternString);
    fclose(data);
    return resultIndex == -1;
}

bool testWithSmallString()
{
    char patternString[10] = "SPBU";
    FILE* data = fopen("DataForTestWithSmallString.txt", "r");
    const int resultIndex = findIndexOfStringInFile(data, patternString);
    fclose(data);
    return resultIndex == -1;
}

bool areTestsPassing()
{
    return standartTest() && testWithEmptyFile() && testWithSmallString();
}