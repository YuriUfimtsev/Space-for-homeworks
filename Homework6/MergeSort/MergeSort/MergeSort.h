#pragma once

#include <stdio.h>
#include <string.h>

// ������� ������ ������ �� ����� � ������.
List* readEntriesFromFile(FILE* data);

// ������� ��������� �������� ������ �� �����.
List* mergeSort(List* listForSorting, enum Key key);