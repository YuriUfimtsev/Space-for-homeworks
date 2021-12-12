#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "AVLTreeTests.h"
#include "AVLTree.h"

bool testOfInsertion()
{
    Node* tree = createNode(25, "ttt");
    advancedInsertToAVLTree(&tree, 30, "aaaa");
    advancedInsertToAVLTree(&tree, 35, "bbbb");
    advancedInsertToAVLTree(&tree, 40, "cccc");
    advancedInsertToAVLTree(&tree, 45, "dddd");
    advancedInsertToAVLTree(&tree, 36, "eeee");
    advancedInsertToAVLTree(&tree, 20, "ffff");
    advancedInsertToAVLTree(&tree, 31, "hhhh");
    advancedInsertToAVLTree(&tree, 20, "replace");
    bool result = getKeyFromAVLTree(tree) == 35 && getBalanceFromAVLTree(tree) == -1
        && getKeyFromAVLTree(getRightChild(tree)) == 40 && getBalanceFromAVLTree(getRightChild(tree)) == 0
        && getKeyFromAVLTree(getLeftChild(tree)) == 25 && getBalanceFromAVLTree(getLeftChild(tree)) == 1
        && strcmp(getValueFromAVLTree(tree, 20), "replace") == 0;
    deleteAVLTree(tree);
    return result;
}

bool testOfRemoving()
{
    Node* tree = createNode(25, "EX");
    advancedInsertToAVLTree(&tree, 30, "aaaa");
    advancedInsertToAVLTree(&tree, 35, "bbbb");
    advancedInsertToAVLTree(&tree, 40, "cccc");
    advancedInsertToAVLTree(&tree, 45, "dddd");
    advancedInsertToAVLTree(&tree, 36, "eeee");
    advancedInsertToAVLTree(&tree, 20, "ffff");
    advancedInsertToAVLTree(&tree, 31, "hhhh");
    advancedRemoveFromAVLTree(tree, 35);
    advancedRemoveFromAVLTree(tree, 25);
    advancedRemoveFromAVLTree(tree, 31);
    advancedRemoveFromAVLTree(tree, 36);
    bool result = getKeyFromAVLTree(tree) == 40 && getBalanceFromAVLTree(tree) == -1
        && getKeyFromAVLTree(getRightChild(tree)) == 45 && getBalanceFromAVLTree(getRightChild(tree)) == 0
        && getKeyFromAVLTree(getLeftChild(tree)) == 30 && getBalanceFromAVLTree(getLeftChild(tree)) == -1;
    deleteAVLTree(tree);
    return result;
}

bool checkOfGettingValue()
{
    Node* tree = createNode(25, "EX");
    advancedInsertToAVLTree(&tree, 30, "aaaa");
    advancedInsertToAVLTree(&tree, 35, "bbbb");
    advancedInsertToAVLTree(&tree, 40, "cccc");
    bool result = strcmp(getValueFromAVLTree(tree, 35), "bbbb") == 0
        && strcmp(getValueFromAVLTree(tree, 25), "EX") == 0;
    deleteAVLTree(tree);
    return result;
}

bool checkOfSearchInTree()
{
    Node* tree = createNode(25, "EX");
    advancedInsertToAVLTree(&tree, 30, "aaaa");
    advancedInsertToAVLTree(&tree, 35, "bbbb");
    bool result = isKeyInAVLTree(tree, 25) && isKeyInAVLTree(tree, 35) && !isKeyInAVLTree(tree, 50);
    deleteAVLTree(tree);
    return result;
}

bool areTestsPassing()
{
    return testOfInsertion() && testOfRemoving()
        && checkOfGettingValue() && checkOfSearchInTree();
}