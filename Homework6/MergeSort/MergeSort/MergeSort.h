#pragma once

#include <stdio.h>
#include <string.h>

// Функция читает данные из файла в список.
List* readEntriesFromFile(FILE* data);

// Функция сортирует слиянием список по ключу.
List* mergeSort(List* listForSorting, enum Key key);