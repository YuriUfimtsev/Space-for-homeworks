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

//int correctNumber(Node* currentNode, enum option side)
//{
//    if (side == left)
//    {
//        if (currentNode->balance <= 0)
//        {
//
//        }
//    }
//}

int calculateBalance(Node* currentNode)
{
    int result = 0;
    if (currentNode->leftChild != NULL)
    {
        result += currentNode->leftChild->balance;
    }
    if (currentNode->rightChild != NULL)
    {
        result += currentNode->rightChild->balance;
    }
    return result;
}

Node* rotateLeft(Node* currentNode)
{
    Node* buffer = currentNode->rightChild;
    if (buffer->balance == 1)
    {
        currentNode->balance = 0;
        buffer->balance = 0;
    }
    else if (buffer->balance == 0)
    {
        buffer->balance = -1;
    }
    currentNode->rightChild = buffer->leftChild;
    buffer->leftChild = currentNode;
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
    Node* firstBuffer = currentNode->rightChild->leftChild;
    Node* secondBuffer = currentNode->rightChild;
    currentNode->rightChild = firstBuffer->leftChild;
    secondBuffer->leftChild = firstBuffer->rightChild;
    firstBuffer->rightChild = secondBuffer;
    firstBuffer->leftChild = currentNode;
    secondBuffer->balance = secondBuffer->leftChild->balance + secondBuffer->rightChild->balance;
    currentNode->balance = currentNode->leftChild->balance + currentNode->rightChild->balance;
    firstBuffer->balance = currentNode->balance + secondBuffer->balance;
    return firstBuffer;
}

Node* bigRotateRight(Node* currentNode)
{
    Node* firstBuffer = currentNode->leftChild->rightChild;
    Node* secondBuffer = currentNode->leftChild;
    secondBuffer->rightChild = firstBuffer->leftChild;
    currentNode->leftChild = firstBuffer->rightChild;
    firstBuffer->leftChild = secondBuffer;
    firstBuffer->rightChild = currentNode;
    secondBuffer->balance = secondBuffer->leftChild->balance + secondBuffer->rightChild->balance;
    currentNode->balance = currentNode->leftChild->balance + currentNode->rightChild->balance;
    firstBuffer->balance = currentNode->balance + secondBuffer->balance;
    return firstBuffer;
}

void updateBalance(Node* currentNode, const int key, bool* areBalancesCorrect)
{
    if (key == currentNode->key)
    {
        if (currentNode->balance == 0)
        {
            *areBalancesCorrect = true;
        }
        return;
    }
    else if (key > currentNode->key)
    {
        updateBalance(currentNode->rightChild, key, areBalancesCorrect);
        if (!*areBalancesCorrect)
        {
            --(currentNode->balance);
        }
        if (currentNode->balance == 0)
        {
            *areBalancesCorrect = true;
        }
    }
    else
    {
        updateBalance(currentNode->leftChild, key, areBalancesCorrect);
        if (!*areBalancesCorrect)
        {
            ++(currentNode->balance);
        }
        if (currentNode->balance == 0)
        {
            *areBalancesCorrect = true;
        }
    }
}

Node* balance(Node* currentNode, bool* isBalance)
{
    if (currentNode->balance == 2)
    {
        *isBalance = true;
        if (currentNode->rightChild->balance >= 0)///
        {
            return rotateLeft(currentNode);
        }
        return bigRotateLeft(currentNode);
    }
    if (currentNode->balance == -2)
    {
        *isBalance = true;
        if (currentNode->leftChild->balance <= 0)
        {
            return rotateRight(currentNode);
        }
        return bigRotateRight(currentNode);
    }
    return currentNode;
}

Node* insertToTree(Node* currentNode, const int key, const char* value, Node* root,
    bool* areBalancesCorrect, bool* isBalance)
{
    if (currentNode == NULL)
    {
        Node* newNode = calloc(1, sizeof(Node));
        if (newNode == NULL)
        {
            return NULL;
        }
        newNode->key = key;
        newNode->value = value;
        if (root == NULL)
        {
            root = newNode;///
        }
        return newNode;
    }
    //if (currentNode->leftChild == NULL && currentNode->rightChild == NULL
    //    && currentNode->value == NULL)
    //{
    //    currentNode->key = key;
    //    currentNode->value = value;
    //    return NULL;
    //}
    if (key > currentNode->key)
    {
        currentNode->rightChild = insertToTree(currentNode->rightChild, key,
            value, root, areBalancesCorrect, isBalance);
        if (*isBalance)
        {
            bool areBalancesCorrecForUpdate = false;
            updateBalance(root, key, &areBalancesCorrecForUpdate);
            *areBalancesCorrect = true;
        }
        if (!*areBalancesCorrect)
        {
            ++(currentNode->balance);
        }
        if (currentNode->balance == 0)
        {
            *areBalancesCorrect = true;
        }
    }
    else
    {
        currentNode->leftChild = insertToTree(currentNode->leftChild, key,
            value, root, areBalancesCorrect, isBalance);
        if (*isBalance)
        {
            bool areBalancesCorrecForUpdate = false;
            updateBalance(root, key, &areBalancesCorrecForUpdate);
            *areBalancesCorrect = true;
        }
        if (!*areBalancesCorrect)
        {
            --(currentNode->balance);
        }
        if (currentNode->balance == 0)
        {
            *areBalancesCorrect = true;
        }
    }
    //else
    //{
    //    free((void*)currentNode->value);
    //    currentNode->value = value;
    //    return NULL;
    //}      ÄËß ÝÒÎÃÎ ÑÄÅËÀÒÜ ÄÐÓÃÓÞ ÔÓÍÊÖÈÞ È ÏÅÐÅÄ ÇÀÏÓÑÊÎÌ ÝÒÎÉ, ÇÀÏÓÑÒÈÒÜ ÄÐÓÃÓÞ È ÏÐÎÂÅÐÈÒÜ, ÅÑÒÜ ËÈ ÄÀÍÍÎÅ ÇÍÀ×ÅÍÈÅ Â ÄÅÐÅÂÅ
    //if (root->)
    Node* newRoot = balance(currentNode, isBalance);
    //if (currentNode == root && isBalance)
    //{
    //    root = newRoot;
    //}
    //else if (isBalance)
    //{
    //    bool areBalancesCorrecForUpdate = false;
    //    updateBalance(root, key, &areBalancesCorrecForUpdate);
    //    *areBalancesCorrect = true;
    //}
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
