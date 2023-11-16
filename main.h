#ifndef MAINH
#define MAINH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module_menu_instructions.h"
#include "module_settings.h"

#define ROW_GRID 6
#define COL_GRID 7

char grid[ROW_GRID][COL_GRID];

enum Player_Type {Human=1, AI};
enum Menu {Play_in_pairs=1, Play_with_ai, Revisualize_game, Statistics, Settings, Instructions, Quit};

#endif