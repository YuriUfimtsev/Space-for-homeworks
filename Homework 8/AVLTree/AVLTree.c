#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "AVLTree.h"

typedef struct Node {
    int key;
    char balance;
    const char* value;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

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
    //free((void*)node->value);
    free(node);
}

void deleteAVLTree(Node* parent)
{
    if (parent == NULL)
    {
        return;
    }
    deleteAVLTree(parent->leftChild);
    deleteAVLTree(parent->rightChild);
    deleteNode(parent);
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
        currentNode->balance = 1;
    }
    currentNode->rightChild = buffer->leftChild;
    buffer->leftChild = currentNode;
    return buffer;
}

Node* rotateRight(Node* currentNode)
{
    Node* buffer = currentNode->leftChild;
    if (buffer->balance == 0)
    {
        currentNode->balance = -1;
        buffer->balance = 1;
    }
    else if (buffer->balance == -1)
    {
        buffer->balance = 0;
        currentNode->balance = 0;
    }
    currentNode->leftChild = buffer->rightChild;
    buffer->rightChild = currentNode;
    return buffer;
}

Node* bigRotateLeft(Node* currentNode)
{
    Node* firstBuffer = currentNode->rightChild->leftChild;
    Node* secondBuffer = currentNode->rightChild;
    if (firstBuffer->balance == 0)
    {
        currentNode->balance = 0;
        firstBuffer->balance = 0;
        secondBuffer->balance = 0;
    }
    else if (firstBuffer->balance == 1)
    {
        currentNode->balance = -1;
        firstBuffer->balance = 0;
        secondBuffer->balance = 0;
    }
    else if (firstBuffer->balance == -1)
    {
        currentNode->balance = 0;
        firstBuffer->balance = 0;
        secondBuffer->balance = 1;
    }
    currentNode->rightChild = firstBuffer->leftChild;
    secondBuffer->leftChild = firstBuffer->rightChild;
    firstBuffer->rightChild = secondBuffer;
    firstBuffer->leftChild = currentNode;
    return firstBuffer;
}

Node* bigRotateRight(Node* currentNode)
{
    Node* firstBuffer = currentNode->leftChild->rightChild;
    Node* secondBuffer = currentNode->leftChild;
    if (firstBuffer->balance == 0)
    {
        currentNode->balance = 0;
        firstBuffer->balance = 0;
        secondBuffer->balance = 0;
    }
    else if (firstBuffer->balance == -1)
    {
        currentNode->balance = 1;
        firstBuffer->balance = 0;
        secondBuffer->balance = 0;
    }
    else if (firstBuffer->balance == 1)
    {
        currentNode->balance = 0;
        firstBuffer->balance = 0;
        secondBuffer->balance = -1;
    }
    secondBuffer->rightChild = firstBuffer->leftChild;
    currentNode->leftChild = firstBuffer->rightChild;
    firstBuffer->leftChild = secondBuffer;
    firstBuffer->rightChild = currentNode;
    return firstBuffer;
}

Node* balance(Node* currentNode, bool* isBalance)
{
    if (currentNode->balance == 2)
    {
        *isBalance = true;
        if (currentNode->rightChild->balance >= 0)
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

void updateBalanceForInsert(Node* currentNode, const int key, bool* areBalancesCorrect)
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
        updateBalanceForInsert(currentNode->rightChild, key, areBalancesCorrect);
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
        updateBalanceForInsert(currentNode->leftChild, key, areBalancesCorrect);
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

void updateBalanceForRemoving(Node* currentNode, const int key, bool* areBalancesCorrect, Node* parent, Node* root)
{
    if (key == currentNode->key)
    {
        if (currentNode->balance == 1 || currentNode->balance == -1 && !*areBalancesCorrect)
        {
            *areBalancesCorrect = true;
        }
        else if (currentNode->balance == 2 || currentNode->balance == -2)
        {
            bool isBalance = false;
            Node* newRoot = balance(currentNode, &isBalance);
            bool areBalancesCorrectForUpdate = false;
            if (root == currentNode)
            {
                root = newRoot;
            }
            else
            {
                parent->rightChild = newRoot;
                updateBalanceForRemoving(newRoot, newRoot->key, &areBalancesCorrectForUpdate, parent, root);
            }
            *areBalancesCorrect = true;
        }
        return;
    }
    else if (key > currentNode->key)
    {
        updateBalanceForRemoving(currentNode->rightChild, key, areBalancesCorrect, currentNode, root);
        if (!*areBalancesCorrect)
        {
            ++(currentNode->balance);
        }
        if (currentNode->balance == 1 || currentNode->balance == -1 && !*areBalancesCorrect)
        {
            *areBalancesCorrect = true;
        }
        else if (currentNode->balance == 2 || currentNode->balance == -2)
        {
            bool isBalance = false;
            Node* newRoot = balance(currentNode, &isBalance);
            bool areBalancesCorrectForUpdate = false;
            if (root == currentNode)
            {
                root = newRoot;
            }
            else
            {
                parent->rightChild = newRoot;
                updateBalanceForRemoving(newRoot, newRoot->key, &areBalancesCorrectForUpdate, parent, root);
            }
            *areBalancesCorrect = true;
        }
    }
    else
    {
        updateBalanceForRemoving(currentNode->leftChild, key, areBalancesCorrect, currentNode, root);
        if (!*areBalancesCorrect)
        {
            --(currentNode->balance);
        }
        if (currentNode->balance == 1 || currentNode->balance == -1 && !*areBalancesCorrect)
        {
            *areBalancesCorrect = true;
        }
        else if (currentNode->balance == 2 || currentNode->balance == -2)
        {
            bool isBalance = false;
            Node* newRoot = balance(currentNode, &isBalance);
            bool areBalancesCorrectForUpdate = false;
            if (root == currentNode)
            {
                root = newRoot;
            }
            else
            {
                parent->leftChild = newRoot;
                updateBalanceForRemoving(newRoot, newRoot->key, &areBalancesCorrectForUpdate, parent, root);////
            }
            *areBalancesCorrect = true;
        }
    }
}

bool findInAVLTree(Node* currentNode, const int key, const char* value)
{
    if (currentNode == NULL)
    {
        return false;
    }
    if (key > currentNode->key)
    {
        return isKeyInAVLTree(currentNode->rightChild, key);
    }
    else if (key < currentNode->key)
    {
        return isKeyInAVLTree(currentNode->leftChild, key);
    }
    else
    {
        //free((void*)currentNode->value);
        currentNode->value = value;
        return true;
    }
}

Node* insertToAVLTree(Node* currentNode, const int key, const char* value, Node* root,
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
            root = newNode;
        }
        return newNode;
    }
    if (currentNode->leftChild == NULL && currentNode->rightChild == NULL
        && currentNode->value == NULL)
    {
        currentNode->key = key;
        currentNode->value = value;
        return currentNode;
    }
    if (key > currentNode->key)
    {
        currentNode->rightChild = insertToAVLTree(currentNode->rightChild, key,
            value, root, areBalancesCorrect, isBalance);
        if (*isBalance)
        {
            bool areBalancesCorrecForUpdate = false;
            updateBalanceForInsert(root, key, &areBalancesCorrecForUpdate);
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
        currentNode->leftChild = insertToAVLTree(currentNode->leftChild, key,
            value, root, areBalancesCorrect, isBalance);
        if (*isBalance)
        {
            bool areBalancesCorrecForUpdate = false;
            updateBalanceForInsert(root, key, &areBalancesCorrecForUpdate);
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
    Node* newRoot = balance(currentNode, isBalance);
    return newRoot;
}

void advancedInsertToAVLTree(Node** root, const int key, const char* value)
{
    if (!findInAVLTree(*root, key, value))
    {
        bool areBalancesCorrect = false;
        bool isBalance = false;
        Node* newRoot = insertToAVLTree(*root, key, value, *root, &areBalancesCorrect, &isBalance);
        if (newRoot != *root)/////
        {
            *root = newRoot;/////
        }
    }
    return;
}

bool isKeyInAVLTree(Node* currentNode, const int key)
{
    if (currentNode == NULL)
    {
        return false;
    }
    if (key > currentNode->key)
    {
        return isKeyInAVLTree(currentNode->rightChild, key);
    }
    else if (key < currentNode->key)
    {
        return isKeyInAVLTree(currentNode->leftChild, key);
    }
    else
    {
        return true;
    }
}

const char* getValue(Node* currentNode, const int key)
{
    if (key == currentNode->key)
    {
        return currentNode->value;
    }
    else if (key > currentNode->key)
    {
        return getValue(currentNode->rightChild, key);
    }
    else
    {
        return getValue(currentNode->leftChild, key);
    }
}

const char* advancedGetValue(Node* root, const int key)
{
    if (isKeyInAVLTree(root, key))
    {
        return getValue(root, key);
    }
    return "NULL";
}

void removeFromAVLTree(Node* currentNode, Node* parent, const int key, Node* root)
{
    if (key > currentNode->key)
    {
        removeFromAVLTree(currentNode->rightChild, currentNode, key, root);
    }
    else if (key < currentNode->key)
    {
        removeFromAVLTree(currentNode->leftChild, currentNode, key, root);
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
                    ++(parent->balance);
                }
                else
                {
                    parent->rightChild = NULL;
                    --(parent->balance);
                }
                deleteNode(currentNode);
                bool areBalancesCorrect = false;
                updateBalanceForRemoving(root, parent->key, &areBalancesCorrect, root, root);
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
                //free(currentNode->value);
                currentNode->value = currentNode->rightChild->value;
                Node* nodeForRemove = currentNode->rightChild;
                currentNode->leftChild = currentNode->rightChild->leftChild;
                currentNode->rightChild = currentNode->rightChild->rightChild;
                free(nodeForRemove);
                currentNode->balance = 0;
                --(parent->balance);
                bool areBalancesCorrect = false;
                updateBalanceForRemoving(root, parent->key, &areBalancesCorrect, root, root);
                return;
            }
            currentNode->key = currentNode->leftChild->key;
            //free((void*)currentNode->value);
            currentNode->value = currentNode->leftChild->value;
            Node* nodeForRemove = currentNode->leftChild;
            currentNode->rightChild = currentNode->leftChild->rightChild;
            currentNode->leftChild = currentNode->leftChild->leftChild;
            free(nodeForRemove);
            currentNode->balance = 0;
            ++(parent->balance);
            bool areBalancesCorrect = false;
            updateBalanceForRemoving(root, parent->key, &areBalancesCorrect, root, root);
        }
        else
        {
            if (currentNode->rightChild->leftChild == NULL)
            {
                currentNode->key = currentNode->rightChild->key;
                //free((void*)currentNode->value);//
                currentNode->value = currentNode->rightChild->value;
                Node* nodeToRemove = currentNode->rightChild;
                currentNode->rightChild = currentNode->rightChild->rightChild;
                free(nodeToRemove);
                --(currentNode->balance);
                bool areBalancesCorrect = false;
                updateBalanceForRemoving(root, currentNode->key, &areBalancesCorrect, root, root);
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
            removeFromAVLTree(currentNode->leftChild, currentNode, currentNode->leftChild->key, root);
        }
    }
}

void advancedRemoveFromAVLTree(Node* root, const int key)
{
    if (!isKeyInAVLTree(root, key))
    {
        return;
    }
    removeFromAVLTree(root, root, key, root);
}

const char* getValueFromAVLTree(Node* currentNode)
{
    return currentNode->value;
}

const int getKeyFromAVLTree(Node* currentNode)
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

char getBalanceFromAVLTree(Node* currentNode)
{
    return currentNode->balance;
}
