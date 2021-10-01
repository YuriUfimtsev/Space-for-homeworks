#include <stdio.h>

#define number 11

int main()
{
    char bracketsString[number] = { '\0' };
    int checkScanf = scanf("%s", bracketsString);
    if (checkScanf != 1)
    {
        printf("We are amazed with your failure");
        return 1;
    }
    int countBrackets = 0;
    for (int i = 0; i < number; ++i)
    {
        if (bracketsString[i] == '(')
        {
            ++countBrackets;
        }
        else if (bracketsString[i] == ')')
        {
            --countBrackets;
        }
        if (countBrackets < 0)
        {
            printf("The rule 'nesting of brackets' isn't fulfilled\n");
            break;
        }
    }
    if (countBrackets == 0)
    {
        printf("The brackets' balance isn't broken\n");
    }
    else
    {
        printf("The brackets' balance is broken\n");
    }
}
