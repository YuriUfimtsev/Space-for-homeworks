#include <stdio.h>

int main()
{
    int a = 0;
    int b = 0;
    printf("Enter numbers a, b \n");
    int const checkScanf = scanf("%d\n %d", &a, &b);
    if (checkScanf != 2)
    {
        printf("We are amazed with your failure");
        return 1;
    }
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    printf("%s %d %s %d\n", "a =", a, "  b =", b);
}
