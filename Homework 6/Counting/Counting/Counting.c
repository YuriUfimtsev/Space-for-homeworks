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

int main()
{
    printf("Enter the quantity of warriors and number of unlucky warriors: ");
    int quantityOfWarriors = 0;
    int numberOfUnluckyWarriors = 0;
    scanf("%d %d", &quantityOfWarriors, &numberOfUnluckyWarriors);
    List* cyclicList = makeListOfWarriors(quantityOfWarriors);
    int const numberOfLastWarrior = deleteListElements(cyclicList, numberOfUnluckyWarriors);
    printf("\nThe number of last warrior: %d\n", numberOfLastWarrior);
    deleteList(cyclicList);
}
