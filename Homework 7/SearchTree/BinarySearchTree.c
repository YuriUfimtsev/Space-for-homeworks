#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    char* value;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

Node* createTree()
{
    return calloc(1, sizeof(Node));
}

void deleteNode(Node* node)
{
    free(node->leftChild);
    free(node->rightChild);
    free(node->value);
    free(node);
}

void deleteTree(Node* root)
{
    if (root == NULL)
    {
        return;
    }
    deleteTree(root->leftChild);
    deleteTree(root->rightChild);
    deleteNode(root);
}

void insertToTree(Node* tree, const int key, char* value)
{
    if (tree == NULL)
    {
        tree->key = key;
        tree->value = value; //????????????
        return;
    }
    if (key > tree->key)
    {
        //if (tree->rightChild == NULL)/// можно и без этих частей обойтись?
        //{///
        //    insertToTree(tree->rightChild, key, value);//
        //    return;///
        //}///
        insertToTree(tree->rightChild, key, value);
    }
    else if (key < tree->key)
    {
        //if (tree->leftChild == NULL)///
        //{///
        //    insertToTree(tree->leftChild, key, value);///
        //    return;///
        //}///
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
    while (key != tree->key)
    {
        if (key > tree->key)
        {
            findInTree(tree->rightChild, key);
        }
        else if (key < tree->key)
        {
            findInTree(tree->leftChild, key);
        }
    }
    return tree->value;
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
            }
            deleteNode(tree);
        }
        else if (tree->leftChild == NULL || tree->rightChild == NULL)
        {
            if (tree->leftChild == NULL)
            {
                tree->key = tree->rightChild->key;
                tree->value = tree->rightChild->value;
                deleteNode(tree->rightChild);
            }
            else if(tree->rightChild == NULL)
            {
                tree->key = tree->leftChild->key;
                tree->value = tree->leftChild->value;
                deleteNode(tree->leftChild);
            }
        }
        else
        {
            if (tree->rightChild->leftChild == NULL)
            {
                tree->key = tree->rightChild->key;
                tree->value = tree->rightChild->value;
                Node* nodeToRemove = tree->rightChild;
                tree->rightChild = tree->rightChild->rightChild;
                deleteNode(nodeToRemove);
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