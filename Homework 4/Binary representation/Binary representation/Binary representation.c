#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

#define SIZE (sizeof(int) * 8)

void sumOfBinaryNumbers(int additionalArrayForSummand[], int lengthOfAdditionalArrayForSummand, int additionalArrayForAddend[], int sumArray[])
{
    int numbersOfUnits = 0;
    for (int i = lengthOfAdditionalArrayForSummand - 1; i >= 0; --i)
    {
        int sum = (additionalArrayForAddend[i] + additionalArrayForSummand[i]);
        if (sum == 0 && numbersOfUnits > 0)
        {
            sumArray[i] = 1;
            --numbersOfUnits;
        }
        else if (sum == 1 && numbersOfUnits > 0)
        {
            sumArray[i] = 0;
        }
        else if (sum == 2 && numbersOfUnits > 0)
        {
            sumArray[i] = 1;
        }
        else if (sum == 2)
        {
            sumArray[i] = 0;
            ++numbersOfUnits;
        }
        else
        {
            sumArray[i] = sum % 2;
        }
    }
}

void readTwosComplementCode(int startNumber, int additionalArray[], int lengthOfArray)
{
    int bit = 1;
    for (int i = lengthOfArray - 1; i >= 0; --i)
    {
        if ((startNumber & bit) == 0)
        {
            additionalArray[i] = 0;
        }
        else
        {
            additionalArray[i] = 1;
        }
        bit = bit << 1;
    }
}

int makeDecimalFromBinary(int additionalArray[], int lengthOfAdditionalArray)
{
    int result = 0;
    int bit = 0;
    for (int i = lengthOfAdditionalArray - 1; i >= 0; --i)
    {
        if ((additionalArray[i] | bit) == 1)
        {
            ++bit;
            result += (bit << (lengthOfAdditionalArray - i - 1));
            bit = 0;
        }
    }
    return result;
}

bool checkOfSum(int summand, int addend, int expectedResult)
{
    if (abs(addend) > abs(summand))
    {
        int buffer = summand;
        summand = addend;
        addend = buffer;
    }
    int additionalArrayForSummand[SIZE] = { 0 };
    readTwosComplementCode(summand, additionalArrayForSummand, SIZE);
    int additionalArrayForAddend[SIZE] = { 0 };
    readTwosComplementCode(addend, additionalArrayForAddend, SIZE);

    int sumArray[SIZE] = { 0 };
    sumOfBinaryNumbers(additionalArrayForSummand, SIZE, additionalArrayForAddend, sumArray);
    int result = makeDecimalFromBinary(sumArray, SIZE);
    return (expectedResult == result);
}

bool standartTestWithPositiveSummand()
{
    return checkOfSum(37, -15, 22);
}

bool standartTestWithNegativeSummand()
{
    return checkOfSum(-58, 12, -46);
}

bool testWithNegativeNumbers()
{
    return checkOfSum(-35, -100, -135);
}

bool testWithPositiveNumbers()
{
    return checkOfSum(200, 801, 1001);
}

bool testWithNull()
{
    return checkOfSum(55, -55, 0);
}

int main()
{
    setlocale(LC_ALL, "Rus");
    if (!standartTestWithNegativeSummand() || !standartTestWithPositiveSummand() || !testWithNegativeNumbers() || !testWithNull())
    {
        printf("Tests failed");
        return -1;
    }
    int summand = 0;
    int addend = 0;
    printf("Введите два числа, сумма которых вас интересует: ");
    scanf("%d %d", &summand, &addend);
    if (abs(addend) > abs(summand))
    {
        int buffer = summand;
        summand = addend;
        addend = buffer;
    }
    int additionalArrayForSummand[SIZE] = { 0 };
    readTwosComplementCode(summand, additionalArrayForSummand, SIZE);
    printf("Большее слагаемое в двоичном представлении в дополнительном коде: ");
    for (int i = 0; i < SIZE; ++i)
    {
        printf(" %d", additionalArrayForSummand[i]);
    }
    int additionalArrayForAddend[SIZE] = { 0 };
    readTwosComplementCode(addend, additionalArrayForAddend, SIZE);
    printf("\nМеньшее слагаемое в двоичном представлении в дополнительном коде: ");
    for (int i = 0; i < SIZE; ++i)
    {
        printf(" %d", additionalArrayForAddend[i]);
    }
    printf("\n");

    int sumArray[SIZE] = { 0 };
    sumOfBinaryNumbers(additionalArrayForSummand, SIZE, additionalArrayForAddend, sumArray);
    printf("Сумма в двоичной системе счисления: ");
    for (int i = 1; i < SIZE; ++i)
    {
        printf(" %d", sumArray[i]);
    }
    int result = makeDecimalFromBinary(sumArray, SIZE);
    printf("\nСумма в десятичной системе счисления: %d\n", result);
}