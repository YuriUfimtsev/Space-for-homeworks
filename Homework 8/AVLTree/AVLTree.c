#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "AVLTree.h"

typedef struct Node {
    int key;
    int balance;
    const char* value;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

typedef struct Tree {
    struct Node* root;
} Tree;

Node* createNode(const int key, const char* value)
{
    Node* newNode = calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return NULL;
    }
    newNode->key = key;
    newNode->value = value;
    return newNode;
}

Node* createEmptyNode()
{
    return calloc(1, sizeof(Node));
}

void deleteNode(Node* node)
{
    free((void*)node->value);
    free(node);
}

void deleteTree(Node* parent)
{
    if (parent == NULL)
    {
        return;
    }
    deleteTree(parent->leftChild);
    deleteTree(parent->rightChild);
    deleteNode(parent);
}

Node* rotateLeft(Node* currentNode)
{
    Node* buffer = currentNode->rightChild;
    currentNode->rightChild = buffer->leftChild;
    buffer->leftChild == currentNode;
    currentNode->balance = currentNode->rightChild->balance + currentNode->leftChild->balance;
    buffer->balance = buffer->rightChild->balance + buffer->leftChild->balance;
    return buffer;
}

Node* rotateRight(Node* currentNode)
{
    Node* buffer = currentNode->leftChild;
    currentNode->leftChild = buffer->rightChild;
    buffer->rightChild = currentNode;
    currentNode->balance = currentNode->rightChild->balance + currentNode->leftChild->balance;
    buffer->balance = buffer->rightChild->balance + buffer->leftChild->balance;
    return buffer;
}

Node* bigRotateLeft(Node* currentNode)
{

}

Node* bigRotateRight(Node* currentNode)
{

}

Node* balance(Node* currentNode)
{
    if (currentNode->balance == 2)
    {
        if (currentNode->rightChild->balance >= 0)///
        {
            return rotateLeft(currentNode);
        }
        return bigRotateLeft(currentNode);
    }
    if (currentNode->balance == -2)
    {
        if (currentNode->leftChild->balance <= 0)
        {
            return rotateRight(currentNode);
        }
        return bigRotateRight(currentNode);
    }
    return currentNode;
}

Node* insertToTree(Node* currentNode, const int key, const char* value)
{
    if (currentNode == NULL)
    {
        Node* newNode = calloc(1, sizeof(Node));
        newNode->key = key;
        newNode->value = value;
        return newNode;
    }
    if (currentNode->leftChild == NULL && currentNode->rightChild == NULL
        && currentNode->value == NULL)
    {
        currentNode->key = key;
        currentNode->value = value;
        return NULL;
    }
    if (key > currentNode->key)
    {
        currentNode->rightChild = insertToTree(currentNode->rightChild, key, value);
        ++(currentNode->balance);
    }
    else if (key < currentNode->key)
    {
        currentNode->leftChild = insertToTree(currentNode->leftChild, key, value);
        --(currentNode->balance);
    }
    else
    {
        free((void*)currentNode->value);
        currentNode->value = value;
        return NULL;
    }
    Node* newRoot = balance(currentNode,...);
    if (...)
    {
        findInTree();
    }
    return newRoot;
}

bool isKeyInTree(Node* currentNode, const int key)
{
    if (currentNode == NULL)
    {
        return false;
    }
    if (key > currentNode->key)
    {
        return isKeyInTree(currentNode->rightChild, key);
    }
    else if (key < currentNode->key)
    {
        return isKeyInTree(currentNode->leftChild, key);
    }
    else
    {
        return true;
    }
}

const char* findInTree(Node* currentNode, const int key)
{
    if (key == currentNode->key)
    {
        return currentNode->value;
    }
    else if (key > currentNode->key)
    {
        return findInTree(currentNode->rightChild, key);
    }
    else
    {
        return findInTree(currentNode->leftChild, key);
    }
}

void removeFromTree(Node* currentNode, Node* parent, const int key)
{
    if (!isKeyInTree(currentNode, key))
    {
        return;
    }
    if (key > currentNode->key)
    {
        removeFromTree(currentNode->rightChild, currentNode, key);
    }
    else if (key < currentNode->key)
    {
        removeFromTree(currentNode->leftChild, currentNode, key);
    }
    else if (key == currentNode->key)
    {
        if (currentNode->leftChild == NULL && currentNode->rightChild == NULL)
        {
            if (parent != currentNode)
            {
                if (parent->leftChild == currentNode)
                {
                    parent->leftChild = NULL;
                }
                else
                {
                    parent->rightChild = NULL;
                }
                deleteNode(currentNode);
                return;
            }
            currentNode->value = NULL;
            currentNode->key = 0;
        }
        else if (currentNode->leftChild == NULL || currentNode->rightChild == NULL)
        {
            if (currentNode->leftChild == NULL)
            {
                currentNode->key = currentNode->rightChild->key;
                free((void*)currentNode->value);
                currentNode->value = currentNode->rightChild->value;
                Node* nodeForRemove = currentNode->rightChild;
                currentNode->leftChild = currentNode->rightChild->leftChild;
                currentNode->rightChild = currentNode->rightChild->rightChild;
                free(nodeForRemove);
                return;
            }
            currentNode->key = currentNode->leftChild->key;
            free((void*)currentNode->value);
            currentNode->value = currentNode->leftChild->value;
            Node* nodeForRemove = currentNode->leftChild;
            currentNode->rightChild = currentNode->leftChild->rightChild;
            currentNode->leftChild = currentNode->leftChild->leftChild;
            free(nodeForRemove);
        }
        else
        {
            if (currentNode->rightChild->leftChild == NULL)
            {
                currentNode->key = currentNode->rightChild->key;
                free((void*)currentNode->value);
                currentNode->value = currentNode->rightChild->value;
                Node* nodeToRemove = currentNode->rightChild;
                currentNode->rightChild = currentNode->rightChild->rightChild;
                free(nodeToRemove);
                return;
            }
            parent = currentNode;
            currentNode = currentNode->rightChild;
            while (currentNode->leftChild->leftChild != NULL)
            {
                currentNode = currentNode->leftChild;
            }
            parent->key = currentNode->leftChild->key;
            parent->value = currentNode->leftChild->value;
            removeFromTree(currentNode->leftChild, currentNode, key);
        }
    }
}

const char* getValueFromTree(Node* currentNode)
{
    return currentNode->value;
}

const int getKeyFromTree(Node* currentNode)
{
    return currentNode->key;
}

Node* getRightChild(Node* currentNode)
{
    return currentNode->rightChild;
}

Node* getLeftChild(Node* currentNode)
{
    return currentNode->leftChild;
}
