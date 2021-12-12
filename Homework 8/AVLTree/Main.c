#pragma warning(disable: 4996 6031)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "AVLTree.h"
#include "AVLTreeTests.h"

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
        printf("Tests failed");
        return -1;
    }
    printTheMenu();
    Node* dictionary = createEmptyNode();
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
            advancedInsertToAVLTree(&dictionary, key, value);
            printf("The new entry has been created\n");
            break;
        case 2:
            strcpy(value, advancedGetValue(dictionary, key));
            printf("The value is '%s'\n", value);
            break;
        case 3:
            printf(isKeyInAVLTree(dictionary, key) ? "This key is in 'Dictionary'\n"
                : "This key doesn't exist in 'Dictionary'\n");
            break;
        case 4:
            advancedRemoveFromAVLTree(dictionary, key);
            break;
        case 5:
            break;
        }
    }
    deleteAVLTree(dictionary);
}
