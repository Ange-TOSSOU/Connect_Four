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
    int score;
}Player;
Player p1, p2;

int **grid;

void initializePlayersHuman(Player*, int);
void initializePlayersAI(Player*, int);
char getMove(Player);

int undoingOneStep(Element**, int**);
void playGame(int, int, int);

int game_not_finish(char*);
int getGameId();
void initializeNumberOfGamesSaved();
int getNumberOfGamesSaved();
Element* saveGameStatus(Element*, int, int, char*);
void saveSettingsStatus(Player, Player, int, int, char*);
Element* saveGamePlay(Player, Player, Element*, int, int, int, int, int);
Element* loadGameStack(int, int, int);
void loadGrid(Element*, int**, int, int);
int loadPlayers(Player*, Player*, int);

#endif