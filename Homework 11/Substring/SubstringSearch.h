#pragma once

#include <stdio.h>

#define MAX_SIZE_OF_STRING 255

// Функция возвращает позицию первого вхождения строки patternString в файле data.
int findIndexOfStringInFile(const char* patternString, const char* dataFromFile);
