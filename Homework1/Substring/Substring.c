#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define maxLengthString 30
#define maxLengthSubstring 40

int main()
{
    printf("Enter the string (less than 30 characters), substring(less than 40 characters): \n");
    char string[maxLengthString] = { "\0" };
    char subString[maxLengthSubstring] = { "\0" };
    int checkScanf = scanf("%s\n %s", string, subString);
    if (checkScanf != 2)
    {
        printf("We ara amazed with your failure");
        return 1;
    }

    int const lengthString = strlen(string);
    int const lengthSubstring = strlen(subString);

    if (lengthSubstring > lengthString)
    {
        printf("SubString in String: 0 times\n");
        return 0;
    }
    if (lengthSubstring == lengthString)
    {
        int checkEquivalence = strcmp(string, subString);
        if (checkEquivalence == 0)
        {
            printf("SubString in String: 1 time\n");
        }
        else
        {
            printf("SubString in String: 0 times\n");
        }
        return 0;
    }

    int countSubstringInString = 0;
    for (int i = 0; i < lengthString; ++i)
    {
        if ((string[i] == subString[0]) && ((lengthString - i) >= lengthSubstring))
        {
            int countForString = i;
            bool checkOfEquivalence = true;
            for (int j = 0; j < lengthSubstring; ++j)
            {
                if (string[countForString] != subString[j])
                {
                    checkOfEquivalence = false;
                    break;
                }
                ++countForString;
            }
            if (checkOfEquivalence)
            {
                ++countSubstringInString;
            }
        }
    }
    printf("SubString in String: %d times", countSubstringInString);
}
