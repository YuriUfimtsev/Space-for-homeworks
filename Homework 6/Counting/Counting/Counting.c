#include <stdio.h>
#include <stdbool.h>

#include "../Counting/CyclicList.h"

cyclicList* makeListOfWarriors(int quantityOfWarriors)
{
    cyclicList* cyclicList = createCyclicList();
    for (int i = 0; i < quantityOfWarriors; ++i)
    {
        add(cyclicList, i + 1);
    }
    return cyclicList;
}

int deleteListElements(cyclicList* cyclicList, int numberOfUnluckyWarriors)
{
    int countForRemove = 1;
    Position* i = first(cyclicList);
    while (sizeOfCyclicList(cyclicList) > 1)
    {
        if (countForRemove % numberOfUnluckyWarriors == 0)
        {
            delete(cyclicList, getValue(cyclicList, i));
        }
        ++countForRemove;
        next(i);
    }
    deletePosition(i);
    Position* startPosition = first(cyclicList);
    const int result = getValue(cyclicList, startPosition);
    deletePosition(startPosition);
    return result;
}

int getNumberOfLastWarrior(const int startQuantityOfWarriors, const int numberOfUnluckyWarriors)
{
    cyclicList* cyclicList = makeListOfWarriors(startQuantityOfWarriors);
    int const numberOfLastWarrior = deleteListElements(cyclicList, numberOfUnluckyWarriors);
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
