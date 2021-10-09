#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* input = fopen("input data.txt", "r");
    if (input == NULL)
    {
        printf("File not found!");
        return 1;
    }
    char a[30] = { '\0' };
    int checkScanf = fscanf(input, "%s", a);
    printf("%s", a);




    ///////
    char* data[30] = { '\0' };
    int linesRead = 0;
    while (!feof(input))
    {
        char* buffer = malloc(sizeof(char) * 30);
        const int readBytes = fscanf(input, "%[^n]", buffer);//fgets(buffer, sizeof(buffer), input);
        if (readBytes < 0)
        {
            break;
        }
        data[linesRead] = buffer;
        ++linesRead;
    }
    for (int i = 0; i < linesRead; ++i)
    {
        printf("%s", data[i]);
    }
    fclose(input);
    ////////////////
    input = fopen("input data.txt", "w");
    //fprintf(input, "hello: %s", "ololo");
    fwrite("Hellow1", sizeof(char), 6, input);// - в данном случае 1 не запишется, т.к. есть ограничение по длине ввода = 6 символов.
    fclose(input);
}

