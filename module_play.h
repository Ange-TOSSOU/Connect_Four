#ifndef PLAYH
#define PLAYH

#include "module_shared.h"
#include "module_grid.h"
#include "module_stack.h"
#include "module_statistics.h"

#define N 30

enum Player_Type {Human=1, AI};

typedef struct
{
    char player_name[N+1];
    int type_of_player;
}Player;
Player p1, p2;

int **grid;

void initializePlayersHuman(Player*, int);
void initializePlayersAI(Player*, int);
char getMove(Player);

int undoingOneStep(Element**, int**);
void playGame(int, int, int, int, int);

void initializeNumberOfGamesSaved();
int getNumberOfGamesSaved();
void saveSettingsStatus(Player, Player, int, Score, char*);
Element* saveGamePlay(Player, Player, Element*, int, int, int, int, Score);

#endif