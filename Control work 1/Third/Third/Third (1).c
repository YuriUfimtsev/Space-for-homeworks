#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE* finput = fopen("File for control work.txt", "r");
    if (finput == NULL)
    {
        printf("File not found!");
        return 1;
    }
    char* data[30] = { '\0' };
    int linesRead = 0;
    while (!feof(finput))
    {
        char* buffer = malloc(sizeof(char) * 30);
        if (finput == NULL)
        {
            printf("wrong");
            return 1;
        }
        const int readBytes = fscanf(finput, "%[^n]", buffer);//fgets(buffer, sizeof(buffer), input);
        if (readBytes < 0)
        {
            break;
        }
        int length = strlen(buffer);
        char* bufferNew = malloc(sizeof(char) * 30);
        int indexOfBufferNew = 0;
        for (int i = 0; i < length + 1; ++i)
            if (buffer[i] != buffer[i + 1])
            {
                bufferNew[indexOfBufferNew] = buffer[i];
                ++indexOfBufferNew;
            }
        data[linesRead] = bufferNew;
        ++linesRead;
    }
    int i = 0;
    for (int i = 0; i < linesRead; ++i)
    {
        printf("%s", data[i]);
    }
    fclose(finput);
}
