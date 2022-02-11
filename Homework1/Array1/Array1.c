#include <stdio.h>

#define number 30

void swapArray(int array[], int lengthArray, int startIndex)
{
    for (int i = 0; i <= ((lengthArray - startIndex - 1) / 2); ++i)
    {
        int buffer = array[startIndex + i];
        array[startIndex + i] = array[lengthArray - i - 1];
        array[lengthArray - i - 1] = buffer;
    }
}

int main()
{
    printf("Enter length of first segment: ");
    int const lengthFirstSegment = 0;
    int checkScanf = scanf("%d", &lengthFirstSegment);
    if (checkScanf != 1)
    {
        printf("We are amazed with your failure");
        return 1;
    }

    printf("Enter length of second segment: ");
    int const lengthSecondSegment = 0;
    checkScanf = scanf("%d", &lengthSecondSegment);
    if (checkScanf != 1)
    {
        printf("We are amazed with your failure");
        return 1;
    }

    printf("Enter elements of array:\n");
    int array[number] = { 0 };
    int const lengthArray = lengthFirstSegment + lengthSecondSegment;
    for (int i = 0; i < lengthArray; ++i)
    {
        checkScanf = scanf("%d", &array[i]);
        if (checkScanf != 1)
        {
            printf("We are amazed with your failure");
            return 1;
        }
    }
    swapArray(array, lengthFirstSegment, 0);
    swapArray(array, lengthArray, lengthFirstSegment);
    swapArray(array, lengthArray, 0);
    printf("The array segments are swapped\n");
    for (int i = 0; i < lengthArray; ++i)
    {
        printf("%d ", array[i]);
    }
}
