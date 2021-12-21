#pragma once

#include <stdio.h>

// Функция возвращает позицию первого вхождения строки patternString в файле data.
int findIndexOfStringInFile(FILE* data, const char* patternString);
