#include <stdio.h>
#include <stdbool.h>

void rewrite(FILE* fileOfNumbers, FILE* fileOfElement, FILE* fileOfResult)
{
	int element = 0;
	fscanf(fileOfElement, "%d", &element);
	while (!feof(fileOfNumbers))
	{
		int buffer = 0;
		fscanf(fileOfNumbers, "%d", &buffer);
		if (buffer < element)
		{
			fprintf(fileOfResult, "%d ", buffer);
		}
	}
}

void checkOfTask()
{
	FILE* fileOfElement = fopen("gTest.txt", "r");
	if (fileOfElement == NULL)
	{
	printf("File not found");
	return -1;
	}
	FILE* fileOfNumbers = fopen("fTest.txt", "r");
	if (fileOfNumbers == NULL)
	{
		printf("File not found");
		fclose(fileOfElement);
		return -1;
	}
	FILE* fileOfResult = fopen("hTest.txt", "w");
	if (fileOfResult == NULL)
	{
		printf("File not found");
		fclose(fileOfElement);
		fclose(fileOfNumbers);
		return -1;
	}
	rewrite(fileOfNumbers, fileOfElement, fileOfResult);
	fclose(fileOfElement);
	fclose(fileOfNumbers);
	fclose(fileOfResult);
}

bool checkFileOfResult()
{
	checkOfTask();
	FILE* fileOfResult = fopen("hTest.txt", "r");
	if (fileOfResult == NULL)
	{
		printf("File not found");
		return -1;
	}
	int resultArray[3] = { 0, -55, 0 };
	int i = 0;
	while (!feof(fileOfResult))
	{
		int checkBuffer = 0;
		fscanf(fileOfResult, "%d", &checkBuffer);
		if (checkBuffer != resultArray[i] && i <= 2)
		{
			fclose(fileOfResult);
			return false;
		}
		++i;
	}
	fclose(fileOfResult);
	return true;
}

int main()
{
	if (!checkFileOfResult())
	{
		printf("Test failed");
		return -1;
	}
	FILE* fileOfElement = fopen("g.txt", "r");
	if (fileOfElement == NULL)
	{
		printf("File not found");
		return -1;
	}
	FILE* fileOfNumbers = fopen("f.txt", "r");
	if (fileOfNumbers == NULL)
	{
		printf("File not found");
		fclose(fileOfElement);
		return -1;
	}
	FILE* fileOfResult = fopen("h.txt", "w");
	if (fileOfResult == NULL)
	{
		printf("File not found");
		fclose(fileOfNumbers);
		fclose(fileOfElement);
		return -1;
	}
	rewrite(fileOfNumbers, fileOfElement, fileOfResult);
	fclose(fileOfElement);
	fclose(fileOfNumbers);
	fclose(fileOfResult);
}
