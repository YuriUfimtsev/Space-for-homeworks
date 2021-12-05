#include "../Counting/TestsForCounting.h"
#include "../Counting/Counting.h"

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