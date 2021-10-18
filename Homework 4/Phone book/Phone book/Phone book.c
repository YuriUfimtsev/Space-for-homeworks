#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    char name[20];
    char phone[15];
} PhoneBookEntry;

void newEntry(int* indexForArray, PhoneBookEntry array[], const char* name, const char* phone)
{
    strcpy(array[*indexForArray].name, name);
    strcpy(array[*indexForArray].phone, phone);
    ++*indexForArray;
}

int findPhoneNumber(int numberOfEntries, PhoneBookEntry array[], char* name)
{
    int j = 0;
    while (strcmp(array[j].name, name) != 0 && j < numberOfEntries)
    {
        ++j;
    }
    return strcmp(array[j].name, name) == 0 ? j : -1;
}

int findName(int numberOfEntries, PhoneBookEntry array[], char* phone)
{
    int j = 0;
    while (strncmp(array[j].phone, phone, strlen(phone)) != 0 && j < numberOfEntries)
    {
        ++j;
    }
    if (strncmp(array[j].phone, phone, strlen(phone)) == 0)
    {
        return j;
    }
    else
    {
        return -1;
    }
}

void saveInFile(FILE* data, int entriesInFile, int numberOfEntries, PhoneBookEntry array[])
{
    for (int j = entriesInFile; j < numberOfEntries; ++j)
    {
        fputs(array[j].name, data);
        fputs(" ", data);
        fputs(array[j].phone, data);
        fputs("\n", data);
    }
}

int readEntriesFromFile(FILE* data, PhoneBookEntry array[])
{
    int i = 0;
    fseek(data, 0, SEEK_END); // ����������� ���������� ��������� � ����� �����
    int position = ftell(data); // ��������� ����� ������� ������ ��������� � �����. ���� ��� = 0, ������ ������ � ����� ����� �������.
    if (position != 0)
    {
        fseek(data, 0, SEEK_SET);
        while (!feof(data))
        {
            int const checkOfEof = fscanf(data, "%s", array[i].name);
            if (checkOfEof == EOF)
            {
                break;
            }
            fscanf(data, "%s", array[i].phone);
            ++i;
        }
    }
    return i;
}

void checkMakingEntryInFile(int indexOfEntries, PhoneBookEntry array[], char* result)
{
    FILE* testForEntry = fopen("TestForEntry.txt", "a");
    int const entriesInFile = indexOfEntries;
    newEntry(&indexOfEntries, array, "Kirill", "20202018");
    newEntry(&indexOfEntries, array, "Sasha", "890055555");
    saveInFile(testForEntry, entriesInFile, indexOfEntries, array);
    fclose(testForEntry);
    testForEntry = fopen("TestForEntry.txt", "r");
    bool checkOfEqual = true;
    char resultOfName[20] = { '\0' };
    char resultOfPhoneNumber[15] = { '\0' };
    for (int i = 0; i < entriesInFile; ++i)
    {
        fscanf(testForEntry, "%s %s", resultOfName, resultOfPhoneNumber);
    }
    for (int j = entriesInFile; j < indexOfEntries; ++j)
    {
        fscanf(testForEntry, "%s %s", resultOfName, resultOfPhoneNumber);
        if (strcmp(array[j].name, resultOfName) != 0 || strcmp(array[j].phone, resultOfPhoneNumber) != 0)
        {
            checkOfEqual = false;
            break;
        }
    }
    fclose(testForEntry);
    remove("TestForEntry.txt");
    strcpy(result, checkOfEqual ? "ok" : "not ok");
}

bool checkPhoneBook(int command, char* expectedResult, char* nameOrNumber)
{
    FILE* test = fopen("Test.txt", "a+");
    if (test == NULL)
    {
        printf("File for tests hasn't been found and couldn't be made");
        return -1;
    }
    PhoneBookEntry array[20] = { '\0' };
    int indexOfEntries = readEntriesFromFile(test, array);
    fclose(test);
    char result[20] = { '\0' };
    if (command == 3)
    {
        int const requiredIndex = findPhoneNumber(indexOfEntries, array, nameOrNumber);
        if (requiredIndex != -1)
        {
            strcpy(result, array[requiredIndex].phone);
        }
    }
    if (command == 4)
    {
        int const requiredIndex = findName(indexOfEntries, array, nameOrNumber);
        if (requiredIndex != -1)
        {
            strcpy(result, array[requiredIndex].name);
        }
    }
    if (command == 5)
    {
        checkMakingEntryInFile(0, array, result);
    }
    return strncmp(expectedResult, result, strlen(expectedResult)) == 0;
}

bool testOfSearchingName()
{
    return checkPhoneBook(4, "Oleg", "8000");
}

bool testOfSearchingPhoneNumber()
{
    return checkPhoneBook(3, "83516789054", "Vasily");
}

bool testOfMakingEntryInFile()
{
    return checkPhoneBook(5, "ok", "none");
}

int main()
{
    if (!testOfSearchingPhoneNumber() || !testOfSearchingName() || !testOfMakingEntryInFile())
    {
        printf("Tests failed");
        return -1;
    }
    PhoneBookEntry array[100] = { '\0' };
    FILE* data = fopen("Data.txt", "a+");
    if (data == NULL)
    {
        printf("File hasn't been found and couldn't be made");
        return -1;
    }
    int indexOfEntries = readEntriesFromFile(data, array);
    fclose(data);
    int entriesInFile = indexOfEntries;
    int command = 1;
    while (command != 0)
    {
        printf("Enter the next case: ");
        scanf("%d", &command);
        
        if (command == 1)
        {
            printf("You will make a new entry. Enter the name and phone: ");
            char name[20] = { '\0' };
            scanf("%s", name);
            char phone[15] = { '\0' };
            scanf("%s", phone);
            newEntry(&indexOfEntries, array, name, phone);
            printf("\n");
        }

        if (command == 2)
        {
            printf("\nEntries which we have now: \n");
            for (int j = 0; j < indexOfEntries; ++j)
            {
                printf("%s - %s", array[j].name, array[j].phone);
                printf("\n");
            }
            printf("\n\n");
        }

        if (command == 3)
        {
            printf("\nEnter the name and I find the phone number of this person: ");
            char name[20] = { '\0' };
            scanf("%s", name);
            int const requiredIndex = findPhoneNumber(indexOfEntries, array, name);
            if (requiredIndex != -1)
            {
                printf("The phone number: %s\n", array[requiredIndex].phone);
            }
            else
            {
                printf("Entry with this name doesn't exist in phone book.\n");
            }
            printf("\n");
        }

        if (command == 4)
        {
            printf("\nEnter the phone number and I find the name of person with this phone number: ");
            char phone[15] = { '\0' };
            scanf("%s", phone);
            int const requiredIndex = findName(indexOfEntries, array, phone);
            if (requiredIndex != -1)
            {
                printf("Name: %s\n", array[requiredIndex].name);
            }
            else
            {
                printf("Entry with this phone number doesn't exist in phone book.\n");
            }
            printf("\n");
        }

        if (command == 5)
        {
            data = fopen("Data.txt", "a");
            saveInFile(data, entriesInFile, indexOfEntries, array);
            fclose(data);
            printf("\nEntries have saved in file.\n");
        }
    }
}
