#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "BinarySearchTree.h"
#include "Dictionary.h"

bool checkOfAddingToTheDictionary()
{
    Dictionary* dictionary = createDictionary();
    addToDictionary(dictionary, 50, "abbba");
    addToDictionary(dictionary, 0, "ccchhh");
    addToDictionary(dictionary, 28, "kkkkmmm");
    if (!(getKeyFromTree(dictionary) == 50 && getKeyFromTree(getLeftChild(dictionary)) == 0
        && getRightChild(dictionary) == NULL
        && getKeyFromTree(getRightChild(getLeftChild(dictionary))) == 28))
    {
        deleteDictionary(dictionary);
        return false;
    }
    if (!(strcmp("abbba", getValueFromTree(dictionary)) == 0
        && strcmp("ccchhh", getValueFromTree(getLeftChild(dictionary))) == 0
        && strcmp("kkkkmmm", getValueFromTree(getRightChild(getLeftChild(dictionary)))) == 0))
    {
        deleteDictionary(dictionary);
        return false;
    }
    deleteDictionary(dictionary);
    return true;
}

bool checkOfGettingValueFromDictionary()
{
    Dictionary* dictionary = createDictionary();
    addToDictionary(dictionary, 50, "abbba");
    addToDictionary(dictionary, 0, "ccchhh");
    bool keyInDictionary = true;
    if (strcmp(getValueFromDictionary(dictionary, 0, &keyInDictionary), "ccchhh") != 0
        || strcmp(getValueFromDictionary(dictionary, 5, &keyInDictionary), "NULL") != 0
        || keyInDictionary)
    {
        deleteDictionary(dictionary);
        return false;
    }
    deleteDictionary(dictionary);
    return true;
}

bool checkOfRemovingFromDictionary()
{
    Dictionary* dictionary = createDictionary();
    addToDictionary(dictionary, 50, "abbba");
    addToDictionary(dictionary, 0, "ccchhh");
    addToDictionary(dictionary, 28, "kkkkmmm");
    removeFromDictionary(dictionary, 50);
    if (getKeyFromTree(dictionary) != 0 || getKeyFromTree(getRightChild(dictionary)) != 28
        || getLeftChild(dictionary) != NULL)
    {
        deleteDictionary(dictionary);
        return false;
    }
    deleteDictionary(dictionary);
    return true;
}

bool areTestsPassing()
{
    return checkOfAddingToTheDictionary()
        && checkOfGettingValueFromDictionary() && checkOfRemovingFromDictionary();
}