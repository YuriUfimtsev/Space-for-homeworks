#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct StatesAndCities StatesAndCities;

typedef struct Graph Graph;

typedef struct Node Node;

// Функция удаляет структуру StatesAndCities.
void deleteStatesAndCities(StatesAndCities* statesAndCities);

// Функция выводит на экран результат работы программы.
// Принимает на вход указатель на структуру StatesAndCities.
void printResult(StatesAndCities* statesAndCities);

// Функция делит свободные города между государствами.
// Принимает на вход указатель на структуру StatesAndCities.
void buildStates(StatesAndCities* statesAndCities);

// Функция заполняет структуру StateAndCities данными из файла.
// Принимает переменную типа FILE*, возвращает указатель на структуру StateAndCities.
StatesAndCities* getDataFromFile(FILE* data);

// Функция возвращает указатель на матрицу, в которой хранится результат работы программы.
// Принимает на вход указатель на структуру StatesAndCities.
int** getResultMatrix(StatesAndCities* statesAndCities);