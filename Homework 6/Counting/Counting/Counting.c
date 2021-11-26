#include <stdio.h>
#include <stdbool.h>

#include "../Counting/CyclicList.h"

cyclicList* makeListOfWarriors(int quantityOfWarriors, int* sizeOfCyclicList)
{
    cyclicList* cyclicList = createCyclicList();
    Position* positionForAdding = first(cyclicList);
    for (int i = 0; i < quantityOfWarriors; ++i)
    {
        addToTheEnd(cyclicList, i + 1, positionForAdding, sizeOfCyclicList);
    }
    deletePosition(positionForAdding);
    return cyclicList;
}

int deleteListElements(cyclicList* cyclicList, int numberOfUnluckyWarriors, int* sizeOfCyclicList)
{
    int countForRemove = 1;
    Position* i = first(cyclicList);
    while (*sizeOfCyclicList > 1)
    {
        if (countForRemove % numberOfUnluckyWarriors == 0)
        {
            delete(cyclicList, getValue(cyclicList, i), i, sizeOfCyclicList);
            ++countForRemove;
        }
        else
        {
            ++countForRemove;
            next(i);
        }
    }
    deletePosition(i);
    Position* startPosition = first(cyclicList);
    const int result = getValue(cyclicList, startPosition);
    deletePosition(startPosition);
    return result;
}

int getNumberOfLastWarrior(const int startQuantityOfWarriors, const int numberOfUnluckyWarriors)
{
    int sizeOfCyclicList = 0;
    cyclicList* cyclicList = makeListOfWarriors(startQuantityOfWarriors, &sizeOfCyclicList);
    int const numberOfLastWarrior = deleteListElements(cyclicList, numberOfUnluckyWarriors, &sizeOfCyclicList);
    deleteCyclicList(cyclicList);
    return numberOfLastWarrior;
}

bool checkOfCounting(const int quantityOfWarriors, const int numberOfUnluckyWarriors,
    const int expectedNumberOfLastWarrior)
{
    int const numberOfLastWarrior = getNumberOfLastWarrior(quantityOfWarriors,
        numberOfUnluckyWarriors);
    return numberOfLastWarrior == expectedNumberOfLastWarrior;
}

bool standartTest()
{
    return checkOfCounting(11, 5, 8);
}

bool testWithSerialDeletion()
{
    return checkOfCounting(15, 1, 15);
}

bool testWithOneWarrior()
{
    return checkOfCounting(1, 3, 1);
}

bool testWithAFewWarriors()
{
    return checkOfCounting(4, 7, 2);
}

bool areTestsPassing()
{
    return standartTest() && testWithSerialDeletion()
        && testWithOneWarrior() && testWithAFewWarriors();
}

int main()
{
    if (!areTestsPassing())
    {
        printf("Tests failed");
        return -1;
    }
    printf("Enter the quantity of warriors and number of unlucky warriors: ");
    int quantityOfWarriors = 0;
    int numberOfUnluckyWarriors = 0;
    scanf("%d %d", &quantityOfWarriors, &numberOfUnluckyWarriors);
    if (quantityOfWarriors == 0 || numberOfUnluckyWarriors == 0)
    {
        printf("\nIncorrect input\n");
        return -1;
    }
    int const numberOfLastWarrior = getNumberOfLastWarrior(quantityOfWarriors,
        numberOfUnluckyWarriors);
    printf("\nThe number of last warrior: %d\n", numberOfLastWarrior);
}
