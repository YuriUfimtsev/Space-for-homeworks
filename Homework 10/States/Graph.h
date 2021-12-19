#pragma once

typedef struct StatesAndCities StatesAndCities;

void deleteStatesAndCities(StatesAndCities* statesAndCities);

void printResult(StatesAndCities* statesAndCities);

void buildStates(StatesAndCities* statesAndCities);

StatesAndCities* getDataFromFile(FILE* data);
