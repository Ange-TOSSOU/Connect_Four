#ifndef SETTINGSH
#define SETTINGSH

#define N_CONFS 100
#define FILE_NAME "conf_settings.txt"
#include "module_menu_instructions.h"

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