#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../SearchTree/BinarySearchTree.h"

Node* createDictionary()
{
    return createNode();
}

void addToDictionary(Node* tree, const int key, char* value)
{
    char* valueForDictionary = malloc(30);
    strcpy(valueForDictionary, value);
    insertToTree(tree, key, valueForDictionary);
}

char* getValueFromDictionary(Node* tree, const int key)
{
    if (!isKeyInTree(tree, key))
    {
        char* value = "NULL";
        return value;
    }
    return findInTree(tree, key);
}

bool isKeyInDictionary(Node* tree, const int key)
{
    return isKeyInTree(tree, key);
}

void removeFromDictionary(Node* tree, const int key)
{
    removeFromTree(tree, tree, key);
}

void deleteDictionary(Node* tree)
{
    deleteTree(tree);
}