#include <stdio.h>
#include <stdbool.h>

#include "List.h"

List* makeListOfWarriors(int quantityOfWarriors)
{
    List* cyclicList = createList();
    for (int i = 0; i < quantityOfWarriors; ++i)
    {
        add(cyclicList, i + 1);
    }
    return cyclicList;
}

int deleteListElements(List* list, int numberOfUnluckyWarriors)
{
    int countForRemove = 1;
    Position* i = first(list);
    while (sizeOfList(list) > 1)
    {
        if (countForRemove % numberOfUnluckyWarriors == 0)
        {
            delete(list, getValue(list, i));
        }
        ++countForRemove;
        i = next(i);
    }
    return getValue(list, first(list));
}

bool checkOfCounting(int quantityOfWarriors, int numberOfUnluckyWarriors, int expectedNumberOfLastWarrior)
{
    List* cyclicList = makeListOfWarriors(quantityOfWarriors);
    int const numberOfLastWarrior = deleteListElements(cyclicList, numberOfUnluckyWarriors);
    deleteList(cyclicList);
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
    return standartTest() && testWithSerialDeletion() && testWithOneWarrior() && testWithAFewWarriors();
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
    List* cyclicList = makeListOfWarriors(quantityOfWarriors);
    int const numberOfLastWarrior = deleteListElements(cyclicList, numberOfUnluckyWarriors);
    printf("\nThe number of last warrior: %d\n", numberOfLastWarrior);
    deleteList(cyclicList);
}
