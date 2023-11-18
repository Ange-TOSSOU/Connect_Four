#ifndef GRIDH
#define GRIDH

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "module_shared.h"
#include "module_settings.h"

char** initializeGrid(int, int);
void printGrid(char**, int, int);
char** deleteGrid(char**, int);
int move(char**, int, int, int);

enum TPlayer {Player1=-1, None, Player2};

#endif