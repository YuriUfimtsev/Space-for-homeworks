#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

#define SIZE (sizeof(int) * 8)

int* makeAnArray(int lengthOfArray)
{
    return calloc(lengthOfArray, sizeof(int));
}

//int findLengthOfBinaryRepresentation(int decimalNumber)
//{
//    int absOfDecimalNumber = abs(decimalNumber);
//    int count = 1;
//    while (absOfDecimalNumber > 1)
//    {
//        absOfDecimalNumber /= 2;
//        ++count;
//    }
//    return count;
//}

void sumOfBinaryNumbers(int additionalArrayForSummand[], int lengthOfAdditionalArrayForSummand, int additionalArrayForAddend[], int sumArray[])
{
    int numbersOfUnits = 0;
    for (int i = 0; i < lengthOfAdditionalArrayForSummand; ++i)
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

void returnToDirectCode(int additionalArray[], int lengthOfAdditionalArray)
{
    if (additionalArray[lengthOfAdditionalArray - 1] == 1)
    {
        int i = 0;
        while (additionalArray[i] != 1 && i < lengthOfAdditionalArray - 1)
        {
            ++i;
        }
        if (additionalArray[i] != 1)
        {
            return -1;
        }
        additionalArray[i] = 0;
        for (int j = 0; j < i; ++j)
        {
            if (additionalArray[j] == 0)
            {
                additionalArray[j] = 1;
            }
        }
        for (int j = 0; j < lengthOfAdditionalArray - 1; ++j)
        {
            additionalArray[j] = (additionalArray[j] + 1) % 2;
        }
    }
}

int makeDecimalFromBinary(int additionalArray[], int lengthOfAdditionalArray)
{
    int result = 0;
    int factor = 1;
    for (int i = 0; i < lengthOfAdditionalArray - 1; ++i)
    {
        result += additionalArray[i] * factor;
        factor *= 2;
    }
    if (additionalArray[lengthOfAdditionalArray - 1] == 1)
    {
        return -result;
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
    int lengthOfAdditionalArrayForSummand = findLengthOfBinaryRepresentation(summand) + 2;
    int* additionalArrayForSummand = makeAnArray(lengthOfAdditionalArrayForSummand);
    if (additionalArrayForSummand == NULL)
    {
        printf("bad");
        return -1;
    }
    readTwosComplementCode(summand, additionalArrayForSummand, lengthOfAdditionalArrayForSummand);
    int lengthOfAdditionalArrayForAddend = lengthOfAdditionalArrayForSummand;
    int* additionalArrayForAddend = makeAnArray(lengthOfAdditionalArrayForAddend);
    if (additionalArrayForAddend == NULL)
    {
        printf("bad");
        return -1;
    }
    readTwosComplementCode(addend, additionalArrayForAddend, lengthOfAdditionalArrayForAddend);

    int* sumArray = makeAnArray(lengthOfAdditionalArrayForSummand);
    if (sumArray == NULL)
    {
        printf("bad");
        return -1;
    }
    sumOfBinaryNumbers(additionalArrayForSummand, lengthOfAdditionalArrayForSummand, additionalArrayForAddend, sumArray);
    returnToDirectCode(sumArray, lengthOfAdditionalArrayForSummand);
    int result = makeDecimalFromBinary(sumArray, lengthOfAdditionalArrayForSummand);
    free(sumArray);
    free(additionalArrayForSummand);
    free(additionalArrayForAddend);
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
    printf("45");
    setlocale(LC_ALL, "Rus");
    //if (!standartTestWithNegativeSummand() || !standartTestWithPositiveSummand() || !testWithNegativeNumbers() || !testWithNegativeNumbers || !testWithNull())
    //{
    //    printf("Tests failed");
    //    return -1;
    //}
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
    if (additionalArrayForSummand == NULL)
    {
        printf("bad");
        return -1;
    }
    readTwosComplementCode(summand, additionalArrayForSummand, SIZE);
    printf("Большее слагаемое в двоичном представлении в дополнительном коде: ");
    for (int i = SIZE - 1; i >= 0; --i)
    {
        printf(" %d", additionalArrayForSummand[i]);
    }
    printf("45");
    int lengthOfAdditionalArrayForAddend = lengthOfAdditionalArrayForSummand;
    int* additionalArrayForAddend = makeAnArray(lengthOfAdditionalArrayForAddend);
    if (additionalArrayForAddend == NULL)
    {
        printf("bad");
        return -1;
    }
    readTwosComplementCode(addend, additionalArrayForAddend, lengthOfAdditionalArrayForAddend);
    printf("\nМеньшее слагаемое в двоичном представлении в дополнительном коде: ");
    for (int i = lengthOfAdditionalArrayForAddend - 1; i >= 0; --i)
    {
        printf(" %d", additionalArrayForAddend[i]);
    }
    printf("\n");




    int* sumArray = makeAnArray(lengthOfAdditionalArrayForSummand);
    if (sumArray == NULL)
    {
        printf("bad");
        return -1;
    }
    sumOfBinaryNumbers(additionalArrayForSummand, lengthOfAdditionalArrayForSummand, additionalArrayForAddend, sumArray);
    printf("Сумма в двоичной системе счисления (дополнительный код): ");
    for (int i = lengthOfAdditionalArrayForSummand - 1; i >= 0; --i)
    {
        printf(" %d", sumArray[i]);
    }
    returnToDirectCode(sumArray, lengthOfAdditionalArrayForSummand);
    printf("\nСумма в двоичной системе счисления (прямой код): ");
    for (int i = lengthOfAdditionalArrayForSummand - 1; i >= 0; --i)
    {
        printf(" %d", sumArray[i]);
    }
    int result = makeDecimalFromBinary(sumArray, lengthOfAdditionalArrayForSummand);
    printf("\nСумма в десятичной системе счисления : %d\n", result);
    free(sumArray);
    free(additionalArrayForSummand);
    free(additionalArrayForAddend);
}
