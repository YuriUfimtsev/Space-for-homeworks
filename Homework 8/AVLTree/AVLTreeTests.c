#include <stdio.h>
#include <stdbool.h>

#include "AVLTreeTests.h"
#include "AVLTree.h"

bool testOfInsertion()
{
    Node* tree = createNode(25, "EX");
    advancedInsertToAVLTree(&tree, 30, "aaaa");
    advancedInsertToAVLTree(&tree, 35, "bbbb");
    advancedInsertToAVLTree(&tree, 40, "cccc");
    advancedInsertToAVLTree(&tree, 45, "dddd");
    advancedInsertToAVLTree(&tree, 36, "eeee");
    advancedInsertToAVLTree(&tree, 20, "ffff");
    advancedInsertToAVLTree(&tree, 31, "hhhh");
    return getKeyFromAVLTree(tree) == 35 && getBalanceFromAVLTree(tree) == -1
        && getKeyFromAVLTree(getRightChild(tree)) == 40 && getBalanceFromAVLTree(getRightChild(tree)) == 0
        && getKeyFromAVLTree(getLeftChild(tree)) == 25 && getBalanceFromAVLTree(getLeftChild(tree)) == 1;
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
}

bool checkOfGettingValue()
{

}

bool checkOfSearchInTree()
{

}
