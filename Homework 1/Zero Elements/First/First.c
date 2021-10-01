#include <stdio.h>
#include <locale.h>

#define number 10

int main()
{
    setlocale(LC_ALL, "Rus");

    int array[number] = { 0 };
    printf("Введите элементы массива: \n");
    for (int i = 0; i < number; ++i)
    {
        int checkScanf = 0;
        checkScanf = scanf("%d", &array[i]);
        if (checkScanf != 1)
        {
            printf("error");
            return 1;
        }
    }

    int count = 0;
    for (int i = 0; i < number; ++i)
    {
        if (array[i] == 0)
        {
            ++count;
        }
    }
    printf("%s %d\n", "Количество нулевых элементов в массиве = ", count);
}