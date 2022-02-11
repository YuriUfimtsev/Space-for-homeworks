#pragma once

#include "../Counting/CyclicList.h"

// ‘ункци€ принимает количество войнов и номер, по которому войны будут убивать друг друга.
// ¬озвращает номер последнего, оставшегос€ в живых, война.
int getNumberOfLastWarrior(const int startQuantityOfWarriors, const int numberOfUnluckyWarriors);