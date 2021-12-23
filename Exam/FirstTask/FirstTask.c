#pragma warning(disable: 4996 6031)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int countRealResult(char string[])
{
    int lengthOfString = (int)strlen(string) - 1;
    int i = 0;
    while (string[i] == '0' || string[i] == '1')
    {
        ++i;
    }
    return i;
}

char* makeDecimalFromBinary(char binaryNumber[])
{
    int lengthOfBinary = countRealResult(binaryNumber);
    int result = 0;
    int factor = 1;
    for (int i = 1; i < lengthOfBinary; ++i)
    {
        factor = factor * 2;
    }
    for (int i = 0; i < lengthOfBinary; ++i)
    {
        result += ((int)binaryNumber[i] - (int)'0') * factor;
        factor = factor / 2;
    }
    char* decimalResult = calloc(lengthOfBinary, sizeof(char));
    if (decimalResult == NULL)
    {
        return "NULL";
    }
    int i = 0;
    while (result != 0)
    {
        int newDigit = result % 10;
        result = result / 10;
        decimalResult[i] = newDigit + '0';
        ++i;
    }
    if (i == 0)
    {
        decimalResult = "0\0";
        return decimalResult;
    }
    int newLength = (int)strlen(decimalResult);
    char* correctDecimalResult = calloc(newLength, sizeof(char));
    if (correctDecimalResult == NULL)
    {
        free(decimalResult);
        return "NULL";
    }
    int j = 0;
    for (int i = newLength - 1; i >= 0; --i)
    {
        correctDecimalResult[j] = decimalResult[i];
        ++j;
    }
    correctDecimalResult[j] = '\0';
    free(decimalResult);
    return correctDecimalResult;
}

bool standartTest()
{
    char binary[5] = "11101";
    char* result = makeDecimalFromBinary(binary);
    int resultOfTest = strcmp(result, "29");
    return resultOfTest == 0;
}

bool testWithZero()
{
    char binary[5] = "0";
    char* result = makeDecimalFromBinary(binary);
    int resultOfTest = strcmp(result, "0");
    return resultOfTest == 0;
}


int main()
{
    if (!standartTest() || !testWithZero())
    {
        printf("Tests failed");
        return;
    }
    printf("Enter the binary number: ");
    char binaryNumber[40] = { '\0' };
    scanf("%s", &binaryNumber);
    char* result = makeDecimalFromBinary(binaryNumber);
    printf("The number in decimal: %s", result);
}

