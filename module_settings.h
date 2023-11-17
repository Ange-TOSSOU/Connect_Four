#ifndef SETTINGSH
#define SETTINGSH

#define N_CONFS 100
#define FILE_NAMED "default_settings.txt"
#define FILE_NAMEP "possible_type_pieces.txt"
#define FILE_NAMEL "possible_level.txt"
#define LINE_D_P 1
#define LINE_D_L 2
#include "module_menu_instructions.h"
#include "module_file.h"

typedef struct
{
    char player1;
    char player2;
}TypePieces;

void initializeDefaultSettings();
void settings();
void printDefaultSettings();

void setDefaultTypePieces(TypePieces);
void setDefaultAILevel(int);
TypePieces getDefaultTypePieces();
int getDefaultAILevel();

#endif