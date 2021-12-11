#include <stdio.h>

#include "AVLTree.h"

int main()
{
    bool areBalancesCorrect = false;
    bool isBalance = false;
    //Node* tree = insertToTree(NULL, 15, "LA", NULL);
    //tree = insertToTree(tree, 28, "KK:):):)", tree);
    //tree = insertToTree(tree, 90, "OOOO", tree);
    //tree = insertToTree(tree, 25, "c", tree);
    //tree = insertToTree(tree, 10, "b", tree);
    Node* tree = insertToTree(NULL, 25, "LA", NULL, &areBalancesCorrect, &isBalance);
    areBalancesCorrect = false;
    isBalance = false;
    tree = insertToTree(tree, 30, "KK:):):)", tree, &areBalancesCorrect, &isBalance);
    areBalancesCorrect = false;
    isBalance = false;
    tree = insertToTree(tree, 40, "OOOO", tree, &areBalancesCorrect, &isBalance);
    areBalancesCorrect = false;
    //tree = insertToTree(tree, 30, "c", tree, &areBalancesCorrect, &isBalance);
    //areBalancesCorrect = false;
    //isBalance = false;
    //tree = insertToTree(tree, 40, "b", tree, &areBalancesCorrect, &isBalance);
    //areBalancesCorrect = false;
    //tree = insertToTree(tree, 18, "KK:):):)", tree, &areBalancesCorrect);
    //areBalancesCorrect = false;
    //tree = insertToTree(tree, 8, "OOOO", tree, &areBalancesCorrect);
    //areBalancesCorrect = false;
    //tree = insertToTree(tree, 23, "c", tree, &areBalancesCorrect);
    //areBalancesCorrect = false;
    //tree = insertToTree(tree, 17, "KK:):):)", tree, &areBalancesCorrect);
    //areBalancesCorrect = false;
    //tree = insertToTree(tree, 22, "OOOO", tree, &areBalancesCorrect);
    //areBalancesCorrect = false;
    //tree = insertToTree(tree, 40, "c", tree, &areBalancesCorrect);
    //areBalancesCorrect = false;
    //tree = insertToTree(tree, 21, "b", tree, &areBalancesCorrect);
    //areBalancesCorrect = false;
    //tree = insertToTree(tree, 50, "KK:):):)", tree, &areBalancesCorrect);
    areBalancesCorrect = false;
    //tree = insertToTree(tree, 40, "a", tree);
}
