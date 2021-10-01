#include <stdio.h>

#define number 28

int main()
{
    int array[number] = { 0 };
    for (int i = 0; i <= 9; ++i)
    {
        for (int j = 0; j <= 9; ++j)
        {
            for (int k = 0; k <= 9; ++k)
            {
                ++array[i + j + k];
            }
        }
    }
    int amount = 0;
    for (int i = 0; i < number; ++i)
    {
        amount += array[i] * array[i];
    }
    printf("%s %d %s\n", "We have", amount, "lucky tickets");
}
