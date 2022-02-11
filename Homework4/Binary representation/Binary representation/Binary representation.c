#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

#define SIZE (sizeof(int) * 8)

void sumOfBinaryNumbers(int arrayForSummand[], int lengthOfArrayForSummand, int arrayForAddend[], int sumArray[])
{
    int numbersOfUnits = 0;
    for (int i = lengthOfArrayForSummand - 1; i >= 0; --i)
    {
        const int sum = arrayForAddend[i] + arrayForSummand[i];
        if (sum == 0 && numbersOfUnits == 1)
        {
            sumArray[i] = 1;
            numbersOfUnits = 0;
        }
        else if (sum == 1 && numbersOfUnits == 1)
        {
            sumArray[i] = 0;
        }
        else if (sum == 2 && numbersOfUnits == 1)
        {
            sumArray[i] = 1;
        }
        else if (sum == 2)
        {
            sumArray[i] = 0;
            numbersOfUnits = 1;
        }
        else
        {
            sumArray[i] = sum % 2;
        }
    }
}

void readTwosComplementCode(int startNumber, int array[], int lengthOfArray)
{
    int bit = 1;
    for (int i = lengthOfArray - 1; i >= 0; --i)
    {
        array[i] = (startNumber & bit) == 0 ? 0 : 1;
        bit = bit << 1;
    }
}

int makeDecimalFromBinary(int array[], int lengthOfArray)
{
    int result = 0;
    for (int i = lengthOfArray - 1; i >= 0; --i)
    {
        if (array[i] == 1)
        {
            result += (1 << (lengthOfArray - i - 1));
        }
    }
    return result;
}

bool checkOfSum(int summand, int addend, int expectedResult)
{
    int arrayForSummand[SIZE] = { 0 };
    readTwosComplementCode(summand, arrayForSummand, SIZE);
    int arrayForAddend[SIZE] = { 0 };
    readTwosComplementCode(addend, arrayForAddend, SIZE);
    int sumArray[SIZE] = { 0 };
    sumOfBinaryNumbers(arrayForSummand, SIZE, arrayForAddend, sumArray);
    int result = makeDecimalFromBinary(sumArray, SIZE);
    return expectedResult == result;
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

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");
    if (argc == 2 && strcmp(argv[1], "tests_only") == 0)
    {
        return standartTestWithNegativeSummand() && standartTestWithPositiveSummand()
            && testWithNegativeNumbers() && testWithNull() ? 0 : -2;
    }
    if (!standartTestWithNegativeSummand() || !standartTestWithPositiveSummand()
        || !testWithNegativeNumbers() || !testWithNull())
    {
        printf("Tests failed");
        return -1;
    }
    int summand = 0;
    int addend = 0;
    printf("Ââåäèòå äâà ÷èñëà, ñóììà êîòîðûõ âàñ èíòåðåñóåò: ");
    scanf("%d %d", &summand, &addend);
    int arrayForSummand[SIZE] = { 0 };
    readTwosComplementCode(summand, arrayForSummand, SIZE);
    printf("Ïåðâîå ñëàãàåìîå â äâîè÷íîì ïðåäñòàâëåíèè â äîïîëíèòåëüíîì êîäå: ");
    for (int i = 0; i < SIZE; ++i)
    {
        printf(" %d", arrayForSummand[i]);
    }
    int arrayForAddend[SIZE] = { 0 };
    readTwosComplementCode(addend, arrayForAddend, SIZE);
    printf("\nÂòîðîå ñëàãàåìîå â äâîè÷íîì ïðåäñòàâëåíèè â äîïîëíèòåëüíîì êîäå: ");
    for (int i = 0; i < SIZE; ++i)
    {
        printf(" %d", arrayForAddend[i]);
    }
    printf("\n");

    int sumArray[SIZE] = { 0 };
    sumOfBinaryNumbers(arrayForSummand, SIZE, arrayForAddend, sumArray);
    printf("Ñóììà â äâîè÷íîé ñèñòåìå ñ÷èñëåíèÿ: ");
    for (int i = 1; i < SIZE; ++i)
    {
        printf(" %d", sumArray[i]);
    }
    int result = makeDecimalFromBinary(sumArray, SIZE);
    printf("\nÑóììà â äåñÿòè÷íîé ñèñòåìå ñ÷èñëåíèÿ: %d\n", result);
}