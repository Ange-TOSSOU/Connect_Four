#ifndef GRIDH
#define GRIDH

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "module_shared.h"
#include "module_settings.h"

int** initializeGrid(int, int);
void printGrid(int**, int, int);
int** deleteGrid(int**, int);
int move(int**, int, int, int);

enum TPlayer {Player1=-1, None, Player2};

#endif