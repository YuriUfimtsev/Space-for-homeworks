#include <stdio.h>
#include <stdbool.h>

#include "../Counting/CyclicList.h"
#include "../Counting/TestsForCounting.h"
#include "../Counting/Counting.h"

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