#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "BinarySearchTree.h"
#include "Dictionary.h"

Dictionary* createDictionary()
{
    return createEmptyNode();
}

void addToDictionary(Dictionary* currentNode, const int key, const char* value)
{
    char* valueForDictionary = malloc(30);
    strcpy(valueForDictionary, value);
    insertToTree(currentNode, key, valueForDictionary);
}

const char* getValueFromDictionary(Dictionary* currentNode, const int key, bool* keyInTree)
{
    if (!isKeyInTree(currentNode, key))
    {
        *keyInTree = false;
        char* value = "NULL";
        return value;
    }
    const char* resultString = findInTree(currentNode, key);
    return resultString;
}

bool isKeyInDictionary(Dictionary* currentNode, const int key)
{
    return isKeyInTree(currentNode, key);
}

void removeFromDictionary(Dictionary* currentNode, const int key)
{
    removeFromTree(currentNode, currentNode, key);
}

void deleteDictionary(Dictionary* currentNode)
{
    deleteTree(currentNode);
}
