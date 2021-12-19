#pragma once

typedef struct StatesAndCities StatesAndCities;

typedef struct Graph Graph;

typedef struct Node Node;

void deleteStatesAndCities(StatesAndCities* statesAndCities);

void printResult(StatesAndCities* statesAndCities);

void buildStates(StatesAndCities* statesAndCities);

StatesAndCities* getDataFromFile(FILE* data);

void printBoolTypeMatrix(bool** matrix, int numberOfRows, int numberOfColumns);

bool** getBoolTypeMatrix(StatesAndCities* statesAndCities);

bool** createMatrixOfRelationsBetweenStatesAndCities(StatesAndCities* stateAndCities);

void deleteBoolTypeMatrix(bool** matrix, int numberOfR);

void printIntTypeMatrix(int** matrix, int numberOfRows, int numberOfColumns);

void createResultStatesMatrix(StatesAndCities* statesAndCities);

int** getIntTypeMatrix(StatesAndCities* statesAndCities);