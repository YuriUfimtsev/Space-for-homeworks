#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "AVLTreeTests.h"
#include "AVLTree.h"

bool testOfInsertion()
{
    Node* tree = createDictionary("25", "ttt");
    insertToDictionary(&tree, "30", "aaaa");
    insertToDictionary(&tree, "35", "bbbb");
    insertToDictionary(&tree, "40", "cccc");
    insertToDictionary(&tree, "45", "dddd");
    insertToDictionary(&tree, "36", "eeee");
    insertToDictionary(&tree, "20", "ffff");
    insertToDictionary(&tree, "31", "hhhh");
    insertToDictionary(&tree, "20", "replace");
    bool isKeyInDictionary = true;
    bool result = strcmp(getKeyFromDictionary(tree), "35") == 0 && getBalanceFromAVLTree(tree) == -1
        && strcmp(getKeyFromDictionary(getRightChild(tree)), "40") == 0 && getBalanceFromAVLTree(getRightChild(tree)) == 0
        && strcmp(getKeyFromDictionary(getLeftChild(tree)), "25") == 0 && getBalanceFromAVLTree(getLeftChild(tree)) == 1
        && strcmp(getValueFromDictionary(tree, "20", &isKeyInDictionary), "replace") == 0 && isKeyInDictionary;
    deleteDictionary(tree);
    return result;
}

bool testOfRemoving()
{
    Node* tree = createDictionary("25", "EX");
    insertToDictionary(&tree, "30", "aaaa");
    insertToDictionary(&tree, "35", "bbbb");
    insertToDictionary(&tree, "40", "cccc");
    insertToDictionary(&tree, "45", "dddd");
    insertToDictionary(&tree, "36", "eeee");
    insertToDictionary(&tree, "20", "ffff");
    insertToDictionary(&tree, "31", "hhhh");
    removeFromDictionary(tree, "35");
    removeFromDictionary(tree, "25");
    removeFromDictionary(tree, "31");
    removeFromDictionary(tree, "36");
    bool result = strcmp(getKeyFromDictionary(tree), "40") == 0 && getBalanceFromAVLTree(tree) == -1
        && strcmp(getKeyFromDictionary(getRightChild(tree)), "45") == 0 && getBalanceFromAVLTree(getRightChild(tree)) == 0
        && strcmp(getKeyFromDictionary(getLeftChild(tree)), "30") == 0 && getBalanceFromAVLTree(getLeftChild(tree)) == -1;
    deleteDictionary(tree);
    return result;
}

bool checkOfGettingValue()
{
    Node* tree = createDictionary("25", "EX");
    insertToDictionary(&tree, "30", "aaaa");
    insertToDictionary(&tree, "35", "bbbb");
    insertToDictionary(&tree, "40", "cccc");
    bool isKeyInDictionary = true;
    bool result = strcmp(getValueFromDictionary(tree, "35", &isKeyInDictionary), "bbbb") == 0
        && strcmp(getValueFromDictionary(tree, "25", &isKeyInDictionary), "EX") == 0
        && isKeyInDictionary;
    deleteDictionary(tree);
    return result;
}

bool checkOfSearchInTree()
{
    Node* tree = createDictionary("25", "EX");
    insertToDictionary(&tree, "30", "aaaa");
    insertToDictionary(&tree, "35", "bbbb");
    bool result = isKeyInDictionary(tree, "25") && isKeyInDictionary(tree, "35") && !isKeyInDictionary(tree, "50");
    deleteDictionary(tree);
    return result;
}

bool testOfLargeTree()
{
    Node* tree = createEmptyDictionary();
    char buffer[valueAndKeySize] = { '\0' };
    for (int i = 0; i < 1000; ++i)
    {
        itoa(i, buffer, 10);
        insertToDictionary(&tree, buffer, buffer);
    }
    int size = 0;
    bool isCorrect = true;
    checkBalance(tree, &isCorrect);
    bool const result = returnSize(tree, &size) == 1000 && isCorrect;
    deleteDictionary(tree);
    return result;
}

bool areTestsPassing()
{
    return testOfInsertion() && testOfRemoving()
        && checkOfGettingValue() && checkOfSearchInTree() && testOfLargeTree();
}
