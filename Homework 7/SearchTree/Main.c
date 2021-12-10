#pragma warning(disable: 4996 6031)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "BinarySearchTree.h"
#include "Dictionary.h"
#include "DictionaryTests.h"

void printTheMenu()
{
    printf("You can use the 'Dictionary'. Enter\n");
    printf("'1' if you want to add the value in 'Dictionary'\n");
    printf("'2' if you want to get the value from 'Dictionary'\n");
    printf("'3' if you want to check the existence of the value(key) in 'Dictionary'\n");
    printf("'4' if you want to remove the value(key) from 'Dictionary'\n");
    printf("'5' if you want to finish the programme\n");
}

int main()
{
    if (!areTestsPassing())
    {
        printf("Tests Failed");
        return -1;
    }
    printTheMenu();
    Dictionary* dictionary = createDictionary();
    int command = 0;
    while (command != 5)
    {
        printf("\nEnter the next command: ");
        scanf("%d", &command);
        int key = 0;
        char value[30] = "";
        bool keyInDictionary = true;
        if (command != 5)
        {
            printf("Enter the key: ");
            scanf("%d", &key);
        }
        switch (command)
        {
        case 1:
            printf("Enter the value: ");
            getc(stdin);
            gets_s(value, 25);
            addToDictionary(dictionary, key, value);
            printf("The new entry has been created\n");
            break;
        case 2:
            strcpy(value, getValueFromDictionary(dictionary, key, &keyInDictionary));
            if (!keyInDictionary)
            {
                printf("The value doesn't exist in 'Dictionary'");
                break;
            }
            printf("The value is '%s'\n", value);
            break;
        case 3:
            printf(isKeyInDictionary(dictionary, key) ? "This key is in 'Dictionary'\n"
                : "This key doesn't exist in 'Dictionary'\n");
            break;
        case 4:
            removeFromDictionary(dictionary, key);
            break;
        case 5:
            break;
        }
    }
    deleteDictionary(dictionary);
}