#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct StatesAndCities StatesAndCities;

typedef struct Graph Graph;

typedef struct Node Node;

// ������� ������� ��������� StatesAndCities.
void deleteStatesAndCities(StatesAndCities* statesAndCities);

// ������� ������� �� ����� ��������� ������ ���������.
// ��������� �� ���� ��������� �� ��������� StatesAndCities.
void printResult(StatesAndCities* statesAndCities);

// ������� ����� ��������� ������ ����� �������������.
// ��������� �� ���� ��������� �� ��������� StatesAndCities.
void buildStates(StatesAndCities* statesAndCities);

// ������� ��������� ��������� StateAndCities ������� �� �����.
// ��������� ���������� ���� FILE*, ���������� ��������� �� ��������� StateAndCities.
StatesAndCities* getDataFromFile(FILE* data);

// ������� ���������� ��������� �� �������, � ������� �������� ��������� ������ ���������.
// ��������� �� ���� ��������� �� ��������� StatesAndCities.
int** getResultMatrix(StatesAndCities* statesAndCities);