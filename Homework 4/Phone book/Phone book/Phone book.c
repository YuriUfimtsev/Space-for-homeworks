#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    char name[20];
    char phone[15];
} PhoneBookEntry;

void newEntry(FILE* data, int indexForArray, PhoneBookEntry array[], char* name, char* phone)
{
    strcpy(array[indexForArray].name, name);
    strcpy(array[indexForArray].phone, phone);
}

int findPhoneNumber(FILE* data, int numberOfEntries, PhoneBookEntry array[], char* name)
{
    int j = 0;
    while (strcmp(array[j].name, name) != 0 && j < numberOfEntries)
    {
        ++j;
    }
    if (strcmp(array[j].name, name) == 0)
    {
        return j;
    }
    else
    {
        return -1;
    }
}

int findName(FILE* data, int numberOfEntries, PhoneBookEntry array[], char* phone)
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
    fseek(data, 0, SEEK_END); // переместили внутренний указатель в конец файла
    int position = ftell(data); // проверили номер позиции нашего указател€ в файле. ≈сли она = 0, значит начало и конец файла совпали.
    if (position != 0)
    {
        fseek(data, 0, SEEK_SET);
        while (!feof(data))
        {
            char buffer[35] = { '\0' };
            fgets(buffer, 35, data);
            if (strlen(buffer) != 0)
            {
                int j = 0;
                char name[20] = { '\0' };
                while (buffer[j] != ' ')
                {
                    name[j] = buffer[j];
                    ++j;
                }
                ++j;
                char phone[15] = { '\0' };
                int counterForPhone = 0;
                while (buffer[j] != '\0')
                {
                    phone[counterForPhone] = buffer[j];
                    ++j;
                    ++counterForPhone;
                }
                strcpy(array[i].name, name);
                strcpy(array[i].phone, phone);
                ++i;
            }
        }
    }
    return i;
}

void checkMakingEntryInFile(int indexOfEntries, PhoneBookEntry array[], FILE* test, char* result)
{
    int const entriesInFile = indexOfEntries;
    newEntry(test, indexOfEntries, array, "Kirill", "20202018");
    newEntry(test, indexOfEntries + 1, array, "Sasha", "890055555");
    saveInFile(test, entriesInFile, indexOfEntries + 2, array);
    fclose(test);
    test = fopen("Test.txt", "r");
    bool checkOfEqual = true;
    char resultOfName[20] = { '\0' };
    char resultOfPhoneNumber[15] = { '\0' };
    for (int i = 0; i < indexOfEntries; ++i)
    {
        fscanf(test, "%s %s", resultOfName, resultOfPhoneNumber);
    }
    for (int j = indexOfEntries; j < indexOfEntries + 2; ++j)
    {
        fscanf(test, "%s %s", resultOfName, resultOfPhoneNumber);
        if (strcmp(array[j].name, resultOfName) != 0)
        {
            checkOfEqual = false;
            break;
        }
        if (strcmp(array[j].phone, resultOfPhoneNumber) != 0)
        {
            checkOfEqual = false;
            break;
        }
    }
    if (checkOfEqual)
    {
        strcpy(result, "ok");
    }
    else
    {
        strcpy(result, "not ok");
    }
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
    char result[20] = { '\0' };
    if (command == 3)
    {
        int const requiredIndex = findPhoneNumber(test, indexOfEntries, array, nameOrNumber);
        if (requiredIndex != -1)
        {
            strcpy(result, array[requiredIndex].phone);
        }
    }
    if (command == 4)
    {
        int const requiredIndex = findName(test, indexOfEntries, array, nameOrNumber);
        if (requiredIndex != -1)
        {
            strcpy(result, array[requiredIndex].name);
        }
    }
    if (command == 5)
    {
        checkMakingEntryInFile(indexOfEntries, array, test, result);
    }
    fclose(test);
    return(strncmp(expectedResult, result, strlen(expectedResult)) == 0);
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
    int entriesInFile = indexOfEntries;
    int command = 1;
    while (command != 0)
    {
        printf("Enter the next command: ");
        scanf("%d", &command);
        
        if (command == 1)
        {
            printf("You will make a new entry. Enter the name and phone: ");
            char name[20] = { '\0' };
            scanf("%s", name);
            char phone[15] = { '\0' };
            scanf("%s", phone);
            newEntry(data, indexOfEntries, array, name, phone);
            ++indexOfEntries;
            printf("\n");
        }

        if (command == 2)
        {
            printf("\nEntries which we have now: \n");
            for (int j = 0; j < indexOfEntries; ++j)
            {
                printf("%s - %s", array[j].name, array[j].phone);
            }
            printf("\n\n");
        }

        if (command == 3)
        {
            printf("\nEnter the name and I find the phone number of this person: ");
            char name[20] = { '\0' };
            scanf("%s", name);
            int const requiredIndex = findPhoneNumber(data, indexOfEntries, array, name);
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
            int const requiredIndex = findName(data, indexOfEntries, array, phone);
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
            saveInFile(data, entriesInFile, indexOfEntries, array);
            printf("\nEntries have saved in file.\n");
        }
    }
    fclose(data);
}
