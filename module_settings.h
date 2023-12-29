#ifndef SETTINGSH
#define SETTINGSH

#include "module_shared.h"
#include "module_menu_instructions.h"
#include "module_file.h"

#define N_CONFS 100
#define LINE_D_P 1
#define LINE_D_L 2

typedef struct
{
    char player1;
    char player2;
}TypePieces;

typedef struct
{
    char player1[ROW_TEXT];
    char player2[ROW_TEXT];
}ColorPieces;

void initializeDefaultSettings();
void settings();
void printDefaultSettings();

void setDefaultTypePieces(TypePieces);
void setDefaultColorPieces(ColorPieces);
void setDefaultAILevel(int);
TypePieces getDefaultTypePieces();
ColorPieces getDefaultColorPieces();
int getDefaultAILevel();

#endif