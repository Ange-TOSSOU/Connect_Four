#ifndef GRIDH
#define GRIDH

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "module_shared.h"
#include "module_settings.h"

int** initializeGrid();
void printGrid(int**);
int** deleteGrid(int**);
int move(int**, int, int);
int win_vertical(int**, int, int);
int win_horizontal(int**, int, int);
int win_diagonal_right(int**, int, int);
int win_diagonal_left(int**, int, int);
int whoWin(int**, int, int);
int getRowTrigger(int**, int);
void saveGridStatus(char*, int**, char);

#endif