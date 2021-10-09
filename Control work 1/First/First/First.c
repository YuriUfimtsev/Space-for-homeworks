#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int sumOfNumbers(element)
{
        int sum = 0;
        int newElement = abs(element);
        while (newElement > 0)
        {
                sum += newElement % 10;
                newElement /= 10;
        }
        return sum;
}

int findElementWithMaxSumOfNumbers(int array[], int lengthOfArray, int additionalArray[])
{
        int maxSumOfNumbers = -1;
        int indexOfAdditionalArray = 0;
        for (int i = 0; i < lengthOfArray; ++i)
        {
                int sum = sumOfNumbers(array[i]);
                if (sum > maxSumOfNumbers)
                {
                        maxSumOfNumbers = sum;
                        indexOfAdditionalArray = 0;
                        additionalArray[indexOfAdditionalArray] = array[i];
                }
                if (sum == maxSumOfNumbers)
                {
                        additionalArray[indexOfAdditionalArray] = array[i];
                        ++indexOfAdditionalArray;
                }
        }
        return(indexOfAdditionalArray);
}

bool checkThisTask(int array[], int lengthOfArray, int expectedArray[])
{
        int* additionalArray = calloc(lengthOfArray, sizeof(int));
        if (additionalArray == NULL)
        {
                printf("bad");
                return -1;
        }
        int indexOfAdditionalArray = findElementWithMaxSumOfNumbers(array, lengthOfArray, additionalArray);
        bool checkOfEquivalence = true;
        for (int i = 0; i < indexOfAdditionalArray; ++i)
        {
                if (additionalArray[i] != expectedArray[i])
                {
                        checkOfEquivalence = false;
                        break;
                }
        }
        free(additionalArray);
        return checkOfEquivalence;
}

bool standartTest()
{
        int array[5] = { 123, 454, -545, 77, 80 };
        int expectedArray[2] = { -545, 77 };
        return(checkThisTask(array, 5, expectedArray));
}

bool testWithEqualNumbers()
{
        int array[4] = { 5, 140, 50, 500 };
        int expectedArray[4] = { 5, 140, 50, 500 };
        return(checkThisTask(array, 4, expectedArray));
}

bool testWithNegativeNumbers()
{
        int array[6] = { -300, -10, -567, -8, -9, 0 };
        int expectedArray[2] = { -567 };
        return(checkThisTask(array, 6, expectedArray));
}

int main()
{
        if (!standartTest() || !testWithEqualNumbers() || !testWithNegativeNumbers())
        {
                printf("Tests failed");
                return -1;
        }
        int array[9] = { -99, 40, 88, 10, 11111, 55, 36, 9, 20 };
        int lengthOfArray = 9;
        printf("Starting array: ");
        for (int i = 0; i < lengthOfArray; ++i)
        {
                printf("%d ", array[i]);
        }
        int* additionalArray = calloc(lengthOfArray, sizeof(int));
        if (additionalArray == NULL)
        {
                printf("bad");
                return -1;
        }
        printf("\nElements with the largest summ of numbers: ");
        int indexOfAdditionalArray = findElementWithMaxSumOfNumbers(array, lengthOfArray, additionalArray);
        for (int i = 0; i < indexOfAdditionalArray; ++i)
        {
                printf("%d ", additionalArray[i]);
        }
        printf("\n");
        free(additionalArray);
}
