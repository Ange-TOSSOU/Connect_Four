#ifndef SHAREDH
#define SHAREDH

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ROW_GRID 6
#define COL_GRID 7
#define ROW_TEXT 80
#define FILE_NAMED "default_settings.txt"
#define FILE_NAMEP "possible_type_pieces.txt"
#define FILE_NAMEL "possible_level.txt"
#define FILE_NAMESP "old_game_play.txt"
#define FILE_NAMESS "old_game_settings.txt"

void printNChar(char, int);
void printOnNChar(char*, int, int);

#endif