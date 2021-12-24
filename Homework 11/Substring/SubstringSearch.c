#pragma warning(disable: 4996)

#include "SubstringSearch.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIMPLE_NUMBER_FOR_HASH 19
#define MODULE_FOR_HASH 109

int calculateHashForString(const char* data, const int startIndex, const int stopIndex)
{
    unsigned int substringLength = stopIndex - startIndex + 1;
    int resultHash = 0;
    int currentNumberForHash = 1;
    for (unsigned int i = 0; i < substringLength; ++i)
    {
        resultHash += data[stopIndex - i] * currentNumberForHash;
        currentNumberForHash *= SIMPLE_NUMBER_FOR_HASH;
    }
    return resultHash % MODULE_FOR_HASH;
}

int calculateMultiplierForNewSubstringSymbol(int lengthOfPatternString)
{
    int result = 1;
    for (int i = 0; i < lengthOfPatternString - 1; ++i)
    {
        result *= SIMPLE_NUMBER_FOR_HASH;
    }
    return result;
}

int calculateHashForNewSubstring(const int wrongHash, const int startNewStringIndex,
    const int stopNewStringIndex, int multiplierForNewSubstringSymbol, const char* data)
{
    int resultHash = wrongHash;
    resultHash -= (data[startNewStringIndex - 1] * multiplierForNewSubstringSymbol) % MODULE_FOR_HASH;
    resultHash *= SIMPLE_NUMBER_FOR_HASH;
    resultHash %= MODULE_FOR_HASH;
    resultHash += data[stopNewStringIndex];
    return resultHash % MODULE_FOR_HASH;
}

bool isStringsEqual(const char* patternString, const char* data, const int startIndex, const int stopIndex)
{
    int indexForPatternString = 0;
    for (int i = startIndex; i < stopIndex; ++i)
    {
        if (patternString[indexForPatternString] != data[i])
        {
            return false;
        }
        ++indexForPatternString;
    }
    return true;
}

int findIndexOfStringInFile(const char* patternString, const char* dataFromFile)
{
    const int patternStringLength = (unsigned int)strlen(patternString);
    int patternStringHash = calculateHashForString(patternString, 0, patternStringLength - 1);
    int dataFromFileLength = strlen(dataFromFile);
    int startIndexOfData = 0;
    if (dataFromFile == NULL)
    {
        return -1;
    }
    if (dataFromFileLength < patternStringLength)
    {
        return -1;
    }
    int currentHash = calculateHashForString(dataFromFile, startIndexOfData, startIndexOfData + patternStringLength - 1);
    if (patternStringHash == currentHash)
    {
        if (isStringsEqual(patternString, dataFromFile, startIndexOfData, startIndexOfData + patternStringLength - 1))
        {
            return startIndexOfData;
        }
    }
    int resultIndex = -2;
    int multiplierForNewSymbol = calculateMultiplierForNewSubstringSymbol(patternStringLength);
    int i = 0;
    while (startIndexOfData + i + patternStringLength - 1 <= dataFromFileLength)
    {
        ++startIndexOfData;
        currentHash = calculateHashForNewSubstring(currentHash, startIndexOfData,
            startIndexOfData + patternStringLength - 1, multiplierForNewSymbol, dataFromFile);
        if (patternStringHash == currentHash)
        {
            if (isStringsEqual(patternString, dataFromFile,
                startIndexOfData, startIndexOfData + patternStringLength - 1))
            {
                resultIndex = startIndexOfData;
                break;
            }
        }
    }
    return resultIndex;
}