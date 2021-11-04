#pragma once

#include <stdbool.h>

typedef struct List List;

typedef struct Position Position;

List* createList();

void deleteList(List* list);

void deletePosition(Position* position);

void add(List* list, Position* position, int value);

Position* first(List* list);

Position* next(Position* position);

bool last(Position* position, List* list);

int getValue(List* list, Position* position);

bool valueInList(List* list, int value);

int sizeOfList(List* list);

bool delete(List* list, int value);

bool last(Position* position, List* list);