#pragma warning(disable: 4996)

#include "../Counting/CyclicList.h"

CyclicList* makeListOfWarriors(int quantityOfWarriors)
{
    CyclicList* cyclicList = createCyclicList();
    Position* positionForAdding = first(cyclicList);
    for (int i = 0; i < quantityOfWarriors; ++i)
    {
        addToTheEnd(cyclicList, i + 1, positionForAdding);
    }
    deletePosition(positionForAdding);
    return cyclicList;
}

int deleteListElements(CyclicList* cyclicList, int numberOfUnluckyWarriors)
{
    if (numberOfUnluckyWarriors == 1)
    {
        return getSizeOfCyclicList(cyclicList);
    }
    int countForRemove = 2;
    Position* i = first(cyclicList);
    while (getSizeOfCyclicList(cyclicList) > 1)
    {
        int size = getSizeOfCyclicList(cyclicList);
        if (countForRemove % numberOfUnluckyWarriors == 0)
        {
            deleteValueFromTheNextPosition(cyclicList, i);
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
    CyclicList* cyclicList = makeListOfWarriors(startQuantityOfWarriors);
    int const numberOfLastWarrior = deleteListElements(cyclicList, numberOfUnluckyWarriors);
    deleteCyclicList(cyclicList);
    return numberOfLastWarrior;
}
