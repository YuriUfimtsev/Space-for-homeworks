#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "AVLTree.h"

typedef struct Node {
    const char* key;
    char balance;
    const char* value;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

const char* getStringToInsert(const char* string)
{
    char* resultString = malloc(valueAndKeySize);
    if (resultString == NULL)
    {
        return NULL;
    }
    strcpy(resultString, string);
    return resultString;
}

Node* createNode(const char* key, const char* value)
{
    Node* newNode = calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return NULL;
    }
    newNode->key = getStringToInsert(key);
    newNode->value = getStringToInsert(value);
    return newNode;
}

Node* createEmptyNode()
{
    return calloc(1, sizeof(Node));
}

void deleteNode(Node* node)
{
    free((void*)node->value);
    free((void*)node->key);
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

void updateBalanceForInsert(Node* currentNode, const char* key, bool* areBalancesCorrect)
{
    if (strcmp(key, currentNode->key) == 0)
    {
        if (currentNode->balance == 0)
        {
            *areBalancesCorrect = true;
        }
    }
    else if (strcmp(key, currentNode->key) > 0)
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

void updateBalanceForRemoving(Node* currentNode, const char* key,
    bool* areBalancesCorrect, Node* parent, Node* root)
{
    if (strcmp(key, currentNode->key) == 0)
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
    else if (strcmp(key, currentNode->key) > 0)
    {
        updateBalanceForRemoving(currentNode->rightChild, key, areBalancesCorrect, currentNode, root);
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
                parent->leftChild = newRoot;
                updateBalanceForRemoving(newRoot, newRoot->key,
                    &areBalancesCorrectForUpdate, parent, root);
            }
            *areBalancesCorrect = true;
        }
    }
}

Node* insertToAVLTreeRecursive(Node* currentNode, const char* key, const char* value, Node* root,
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
        return newNode;
    }
    if (currentNode->leftChild == NULL && currentNode->rightChild == NULL
        && currentNode->value == NULL)
    {
        currentNode->key = key;
        currentNode->value = value;
        return currentNode;
    }
    if (strcmp(key, currentNode->key) > 0)
    {
        currentNode->rightChild = insertToAVLTreeRecursive(currentNode->rightChild, key,
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
        currentNode->leftChild = insertToAVLTreeRecursive(currentNode->leftChild, key,
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

Node* isKeyInAVLTree(Node* currentNode, const char* key)
{
    if (currentNode == NULL || currentNode->value == NULL)
    {
        return NULL;
    }
    if (strcmp(key, currentNode->key) > 0)
    {
        return isKeyInAVLTree(currentNode->rightChild, key);
    }
    else if (strcmp(key, currentNode->key) < 0)
    {
        return isKeyInAVLTree(currentNode->leftChild, key);
    }
    else
    {
        return currentNode;
    }
}

bool findInAVLTreeAndReplace(Node* tree, const char* key, const char* value)
{
    Node* currentNode = isKeyInAVLTree(tree, key);
    if (currentNode == NULL)
    {
        return false;
    }
    free((void*)currentNode->value);
    currentNode->value = getStringToInsert(value);
    return true;
}

void insertToAVLTree(Node** root, const char* key, const char* value)
{
    if (findInAVLTreeAndReplace(*root, key, value))
    {
        return;
    }
    bool areBalancesCorrect = false;
    bool isBalance = false;
    Node* newRoot = insertToAVLTreeRecursive(*root, getStringToInsert(key), getStringToInsert(value),
        *root, &areBalancesCorrect, &isBalance);
    if (newRoot != *root)
    {
        *root = newRoot;
    }
}

Node* getNodeFromAVLTree(Node* tree, const char* key)
{
    Node* currentNode = isKeyInAVLTree(tree, key);
    if (currentNode == NULL)
    {
        return NULL;
    }
    return currentNode;
}

const char* advancedGetValue(Node* root, const char* key, bool* isKeyInDictionary)
{
    Node* currentNode = getNodeFromAVLTree(root, key);
    if (currentNode == NULL)
    {
        *isKeyInDictionary = false;
        return "NULL";
    }
    return currentNode->value;
}

void removeRightChildParent(Node* currentNode)
{
    free((void*)currentNode->value);
    currentNode->value = currentNode->rightChild->value;
    free((void*)currentNode->key);
    currentNode->key = currentNode->rightChild->key;
    Node* nodeForRemove = currentNode->rightChild;
    currentNode->leftChild = currentNode->rightChild->leftChild;
    currentNode->rightChild = currentNode->rightChild->rightChild;
    free(nodeForRemove);
    currentNode->balance = 0;
}

void removeLeftChildParent(Node* currentNode)
{
    free((void*)currentNode->value);
    currentNode->value = currentNode->leftChild->value;
    free((void*)currentNode->key);
    currentNode->key = currentNode->leftChild->key;
    Node* nodeForRemove = currentNode->leftChild;
    currentNode->leftChild = currentNode->leftChild->leftChild;
    currentNode->rightChild = currentNode->leftChild->rightChild;
    free(nodeForRemove);
    currentNode->balance = 0;
}

void removeSpecialRightChildParent(Node* currentNode)
{
    free((void*)currentNode->value);
    currentNode->value = currentNode->rightChild->value;
    free((void*)currentNode->key);
    currentNode->key = currentNode->rightChild->key;
    Node* nodeForRemove = currentNode->rightChild;
    currentNode->rightChild = currentNode->rightChild->rightChild;
    free(nodeForRemove);
}

void changeBeforeRemoving(Node* parent, Node* currentNode)
{
    const char* keyToRemove = parent->key;
    parent->key = currentNode->leftChild->key;
    const char* valueForRemove = parent->value;
    parent->value = currentNode->leftChild->value;
    currentNode->leftChild->value = valueForRemove;
    currentNode->leftChild->key = keyToRemove;
}

void removeFromAVLTree(Node* currentNode, Node* parent, const char* key, Node* root)
{
    if (strcmp(key, currentNode->key) > 0)
    {
        removeFromAVLTree(currentNode->rightChild, currentNode, key, root);
    }
    else if (strcmp(key, currentNode->key) < 0)
    {
        removeFromAVLTree(currentNode->leftChild, currentNode, key, root);
    }
    else if (strcmp(key, currentNode->key) == 0)
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
            currentNode->key = NULL;
        }
        else if (currentNode->leftChild == NULL || currentNode->rightChild == NULL)
        {
            if (currentNode->leftChild == NULL)
            {
                removeRightChildParent(currentNode);
                --(parent->balance);
                bool areBalancesCorrect = false;
                updateBalanceForRemoving(root, parent->key, &areBalancesCorrect, root, root);
                return;
            }
            removeLeftChildParent(currentNode);
            ++(parent->balance);
            bool areBalancesCorrect = false;
            updateBalanceForRemoving(root, parent->key, &areBalancesCorrect, root, root);
        }
        else
        {
            if (currentNode->rightChild->leftChild == NULL)
            {
                removeSpecialRightChildParent(currentNode);
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
            changeBeforeRemoving(parent, currentNode);
            removeFromAVLTree(currentNode->leftChild, currentNode, currentNode->leftChild->key, root);
        }
    }
}

void advancedRemoveFromAVLTree(Node* root, const char* key)
{
    if (!isKeyInAVLTree(root, key))
    {
        return;
    }
    removeFromAVLTree(root, root, key, root);
}

const char* getValue(Node* currentNode)
{
    return currentNode->value;
}

const char* getKeyFromAVLTree(Node* currentNode)
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

Node* createEmptyDictionary()
{
    return createEmptyNode();
}

Node* createDictionary(const char* key, const char* value)
{
    return createNode(key, value);
}

void deleteDictionary(Node* dictionary)
{
    deleteAVLTree(dictionary);
}

const char* getValueFromDictionary(Node* dictionary, const char* key, bool* isKeyInDictionary)
{
    return advancedGetValue(dictionary, key, isKeyInDictionary);
}

void insertToDictionary(Node** dictionary, const char* key, const char* value)
{
    insertToAVLTree(dictionary, key, value);
}

bool isKeyInDictionary(Node* dictionary, const char* key)
{
    return isKeyInAVLTree(dictionary, key);
}

void removeFromDictionary(Node* dictionary, const char* key)
{
    advancedRemoveFromAVLTree(dictionary, key);
}

const char* getKeyFromDictionary(Node* dictionaryValue)
{
    return getKeyFromAVLTree(dictionaryValue);
}

int checkBalance(Node* currentNode, bool* isCorrect)
{
    if (currentNode == NULL)
    {
        return 0;
    }
    const int leftHeight = currentNode->leftChild != NULL ? checkBalance(currentNode->leftChild, isCorrect) : 0;
    const int rightHeight = currentNode->rightChild != NULL ? checkBalance(currentNode->rightChild, isCorrect) : 0;
    *isCorrect = *isCorrect ? abs(leftHeight - rightHeight) < 2 : false;
    if (rightHeight >= leftHeight)
    {
        return rightHeight + 1;
    }
    return leftHeight + 1;
}

bool checkOfDifferenceBetweenChildren(Node* currentNode)
{
    return strcmp(currentNode->key, currentNode->rightChild->key) < 0
        && strcmp(currentNode->key, currentNode->leftChild->key) > 0;
}

int returnSize(Node* currentNode, int* size)
{
    if (currentNode == NULL)
    {
        return *size;
    }
    if (currentNode->leftChild != NULL && currentNode->rightChild != NULL)
    {
        if (!checkOfDifferenceBetweenChildren(currentNode))
        {
            return -1;
        }
        returnSize(currentNode->leftChild, size);
        ++(*size);
        returnSize(currentNode->rightChild, size);
        ++(*size);
    }
    else if (currentNode->leftChild == NULL)
    {
        if (currentNode->rightChild == NULL)
        {
            return *size;
        }
        ++(*size);
        returnSize(currentNode->rightChild, size);
    }
    else if (currentNode->rightChild == NULL)
    {
        if (currentNode->leftChild == NULL)
        {
            return *size;
        }
        ++(*size);
        returnSize(currentNode->leftChild, size);
    }
    return *size + 1;
}