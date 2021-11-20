#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../SearchTree/BinarySearchTree.h"

Node* createNode()
{
    return calloc(1, sizeof(Node));
}

void deleteNode(Node* node)
{
    free(node->value);
    free(node);
}

void deleteTree(Node* root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->leftChild != NULL)
    {
        deleteTree(root->leftChild);
    }
    if (root->rightChild != NULL)
    {
        deleteTree(root->rightChild);
    }
    deleteNode(root);
}

void insertToTree(Node* tree, const int key, char* value)
{
    if (tree->leftChild == NULL && tree->rightChild == NULL
        && tree->value == NULL)
    {
        tree->key = key;
        tree->value = value;
        return;
    }
    if (key > tree->key)
    {
        if (tree->rightChild == NULL)
        {
            Node* newNode = createNode();
            tree->rightChild = newNode;
            newNode->key = key;
            newNode->value = value;
            return;
        }
        insertToTree(tree->rightChild, key, value);
    }
    else if (key < tree->key)
    {
        if (tree->leftChild == NULL)
        {
            Node* newNode = createNode();
            tree->leftChild = newNode;
            newNode->key = key;
            newNode->value = value;
            return;
        }
        insertToTree(tree->leftChild, key, value);
    }
    else if (key == tree->key)
    {
        tree->value = value;
    }
}

bool isKeyInTree(Node* tree, const int key)
{
    if (tree == NULL)
    {
        return false;
    }
    if (key > tree->key)
    {
        if (tree->rightChild == NULL)
        {
            return false;
        }
        isKeyInTree(tree->rightChild, key);
    }
    else if (key < tree->key)
    {
        if (tree->leftChild == NULL)
        {
            return false;
        }
        isKeyInTree(tree->leftChild, key);
    }
    else if (key == tree->key)
    {
        return true;
    }
}

char* findInTree(Node* tree, const int key)
{
    if (key == tree->key)
    {
        return tree->value;
    }
    if (key > tree->key)
    {
        findInTree(tree->rightChild, key);
    }
    else if (key < tree->key)
    {
        findInTree(tree->leftChild, key);
    }
}

void removeFromTree(Node* tree, Node* root, const int key)
{
    if (!isKeyInTree(tree, key))
    {
        return;
    }
    if (key > tree->key)
    {
        removeFromTree(tree->rightChild, tree, key);
    }
    else if (key < tree->key)
    {
        removeFromTree(tree->leftChild, tree, key);
    }
    else if (key == tree->key)
    {
        if (tree->leftChild == NULL && tree->rightChild == NULL)
        {
            if (root != tree)
            {
                if (root->leftChild == tree)
                {
                    root->leftChild = NULL;
                }
                else
                {
                    root->rightChild = NULL;
                }
                deleteNode(tree);
            }
            else if (root == tree)
            {
                tree->value = NULL;
                tree->key = 0;
            }
        }
        else if (tree->leftChild == NULL || tree->rightChild == NULL)
        {
            if (tree->leftChild == NULL)
            {
                tree->key = tree->rightChild->key;
                free(tree->value);
                tree->value = tree->rightChild->value;
                Node* nodeForRemove = tree->rightChild;
                tree->leftChild = tree->rightChild->leftChild;
                tree->rightChild = tree->rightChild->rightChild;
                free(nodeForRemove);
            }
            else if(tree->rightChild == NULL)
            {
                tree->key = tree->leftChild->key;
                free(tree->value);
                tree->value = tree->leftChild->value;
                Node* nodeForRemove = tree->leftChild;
                tree->rightChild = tree->leftChild->rightChild;
                tree->leftChild = tree->leftChild->leftChild;
                free(nodeForRemove);
            }
        }
        else
        {
            if (tree->rightChild->leftChild == NULL)
            {
                tree->key = tree->rightChild->key;
                free(tree->value);
                tree->value = tree->rightChild->value;
                Node* nodeToRemove = tree->rightChild;
                tree->rightChild = tree->rightChild->rightChild;
                free(nodeToRemove);
                return;
            }
            root = tree;
            tree = tree->rightChild;
            while (tree->leftChild->leftChild != NULL)
            {
                tree = tree->leftChild;
            }
            root->key = tree->leftChild->key;
            root->value = tree->leftChild->value;
            removeFromTree(tree->leftChild, tree, key);
        }
    }
}
