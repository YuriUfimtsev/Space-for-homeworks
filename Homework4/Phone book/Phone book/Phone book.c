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
    while (j < numberOfEntries && strcmp(array[j].name, name))
    {
        ++j;
    }
    return strcmp(array[j].name, name) == 0 ? j : -1;
}

int findName(int numberOfEntries, PhoneBookEntry array[], char* phone)
{
    int j = 0;
    while (j < numberOfEntries && strncmp(array[j].phone, phone, strlen(phone)) != 0)
    {
        ++j;
    }
    return strncmp(array[j].phone, phone, strlen(phone)) == 0 ? j : -1;
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
    fseek(data, 0, SEEK_END); // переместили внутренний указатель в конец файла
    int position = ftell(data); // проверили номер позиции нашего указател€ в файле. ≈сли она = 0, значит начало и конец файла совпали.
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

int main(int argc, char* argv[])
{
    if (argc == 2 && strcmp(argv[1], "tests_only") == 0)
    {
        return testOfSearchingPhoneNumber() &&
            testOfSearchingName() && testOfMakingEntryInFile() ? 0 : -2;
    }
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
    int command = -1;
    printf("You can use following commands.\n");
    printf("1 - exit the programme.\n");
    printf("2 - make a new entry (write number and phone).\n");
    printf("3 - find the phone of person (write the person's name).\n");
    printf("4 - find the name of person, which phone number we known (write the person's telephone number)\n");
    printf("5 - save all entries in file.\n");
    while (command != 0)
    {
        printf("\nEnter the next command: ");
        scanf("%d", &command);
        switch (command)
        {
            case 1:
                printf("You will make a new entry. Enter the name and phone: ");
                char name[20] = { '\0' };
                scanf("%s", name);
                char phone[15] = { '\0' };
                scanf("%s", phone);
                newEntry(&indexOfEntries, array, name, phone);
                printf("\n");
                break;
            case 2:
                printf("\nEntries which we have now: \n");
                for (int j = 0; j < indexOfEntries; ++j)
                {
                    printf("%s - %s", array[j].name, array[j].phone);
                    printf("\n");
                }
                printf("\n\n");
                break;
            case 3:
                printf("\nEnter the name and I find the phone number of this person: ");
                scanf("%s", name);
                int requiredIndex = findPhoneNumber(indexOfEntries, array, name);
                if (requiredIndex != -1)
                {
                    printf("The phone number: %s\n", array[requiredIndex].phone);
                }
                else
                {
                    printf("Entry with this name doesn't exist in phone book.\n");
                }
                printf("\n");
                break;
            case 4:
                printf("\nEnter the phone number and I find the name of person with this phone number: ");
                scanf("%s", phone);
                requiredIndex = findName(indexOfEntries, array, phone);
                if (requiredIndex != -1)
                {
                    printf("Name: %s\n", array[requiredIndex].name);
                }
                else
                {
                    printf("Entry with this phone number doesn't exist in phone book.\n");
                }
                printf("\n");
                break;
            case 5:
                data = fopen("Data.txt", "a");
                saveInFile(data, entriesInFile, indexOfEntries, array);
                fclose(data);
                printf("\nEntries have saved in file.\n");
                break;
        }
    }
}
