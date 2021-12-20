#pragma warning(disable: 4996 6011 6031)

#include "SubstringSearch.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIMPLE_NUMBER_FOR_HASH 19
#define MODULE_FOR_HASH 109

int calculateHashForString(char* substring)
{
    unsigned int substringLength = (unsigned int)strlen(substring);
    int resultHash = 0;
    int currentNumberForHash = 1;
    for (unsigned int i = 0; i < substringLength; ++i)
    {
        resultHash += substring[substringLength - i - 1] * currentNumberForHash;
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

int calculateHashForNewSubstring(const int wrongHash, char* outdatedSubstring,
    const char newSymbol, const unsigned int lengthOfSubstring, int multiplierForNewSubstringSymbol)
{
    int resultHash = wrongHash;
    resultHash -= (outdatedSubstring[0] * multiplierForNewSubstringSymbol) % MODULE_FOR_HASH;
    resultHash *= SIMPLE_NUMBER_FOR_HASH;
    resultHash %= MODULE_FOR_HASH;
    resultHash += newSymbol;
    return resultHash % MODULE_FOR_HASH;
}

int findIndexOfStringInFile(FILE* data, char* patternString)
{
    const unsigned int patternStringLength = (unsigned int)strlen(patternString);
    int patternStringHash = calculateHashForString(patternString);
    unsigned int indexInFile = 0;
    char symbolFromFile = ' ';
    char* substring = (char*)calloc(patternStringLength + 1, sizeof(char));
    while (indexInFile < patternStringLength && fscanf(data, "%c", &symbolFromFile) > 0)
    {
        substring[indexInFile] = symbolFromFile;
        ++indexInFile;
    }
    if (indexInFile < patternStringLength - 1)
    {
        return -1;
    }
    int currentHash = calculateHashForString(substring);
    if (patternStringHash == currentHash)
    {
        if (strcmp(patternString, substring) == 0)
        {
            return indexInFile - patternStringLength;
        }
    }
    int resultIndex = -2;
    int multiplierForNewSymbol = calculateMultiplierForNewSubstringSymbol(patternStringLength);
    while (fscanf(data, "%c", &symbolFromFile) > 0)
    {
        ++indexInFile;
        int hjjjhash = calculateHashForString(substring);
        currentHash = calculateHashForNewSubstring(currentHash, substring, symbolFromFile,
            patternStringLength, multiplierForNewSymbol);
        for (unsigned int i = 0; i < patternStringLength - 1; ++i)
        {
            substring[i] = substring[i + 1];
        }
        substring[patternStringLength - 1] = symbolFromFile;
        int hhash = calculateHashForString(substring);
        if (patternStringHash == currentHash)
        {
            if (strcmp(patternString, substring) == 0)
            {
                resultIndex = indexInFile - patternStringLength;
                break;
            }
        }
    }
    free(substring);
    return resultIndex;
}