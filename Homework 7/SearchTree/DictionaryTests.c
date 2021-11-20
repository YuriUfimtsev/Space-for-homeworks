#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../SearchTree/BinarySearchTree.h"
#include "../SearchTree/Dictionary.h"

bool checkOfAddingToTheDictionary()
{
    Node* dictionary = createDictionary();
    char firstStringForCheck[8] = "abbba";
    char secondStringForCheck[8] = "ccchhh";
    char thirdStringForCheck[8] = "kkkkmmm";
    addToDictionary(dictionary, 50, firstStringForCheck);
    addToDictionary(dictionary, 0, secondStringForCheck);
    addToDictionary(dictionary, 28, thirdStringForCheck);
    if (!(dictionary->key == 50 && dictionary->leftChild->key == 0
        && dictionary->rightChild == NULL
        && dictionary->leftChild->rightChild->key == 28))
    {
        deleteDictionary(dictionary);
        return false;
    }
    if (!(strcmp(firstStringForCheck, dictionary->value) == 0
        && strcmp(secondStringForCheck, dictionary->leftChild->value) == 0
        && strcmp(thirdStringForCheck, dictionary->leftChild->rightChild->value) == 0))
    {
        deleteDictionary(dictionary);
        return false;
    }
    deleteDictionary(dictionary);
    return true;
}

bool checkOfGettingValueFromDictionary()
{
    Node* dictionary = createDictionary();
    char firstStringForCheck[8] = "abbba";
    char secondStringForCheck[8] = "ccchhh";
    char thirdStringForCheck[5] = "NULL";
    addToDictionary(dictionary, 50, firstStringForCheck);
    addToDictionary(dictionary, 0, secondStringForCheck);
    if (strcmp(getValueFromDictionary(dictionary, 0), secondStringForCheck) != 0
        || strcmp(getValueFromDictionary(dictionary, 5), thirdStringForCheck) != 0)
    {
        deleteDictionary(dictionary);
        return false;
    }
    deleteDictionary(dictionary);
    return true;
}

bool checkOfRemovingFromDictionary()
{
    Node* dictionary = createDictionary();
    char firstStringForCheck[8] = "abbba";
    char secondStringForCheck[8] = "ccchhh";
    char thirdStringForCheck[8] = "kkkkmmm";
    addToDictionary(dictionary, 50, firstStringForCheck);
    addToDictionary(dictionary, 0, secondStringForCheck);
    addToDictionary(dictionary, 28, thirdStringForCheck);
    removeFromDictionary(dictionary, 50);
    if (dictionary->key != 0 || dictionary->rightChild->key != 28
        || dictionary->leftChild != NULL)
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