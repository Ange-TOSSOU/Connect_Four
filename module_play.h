#ifndef PLAYH
#define PLAYH

#include "module_shared.h"
#include "module_grid.h"
#include "module_stack.h"
#include "module_statistics.h"

void initializePlayersHuman(Player*, int);
void initializePlayersAI(Player*, int);
char getMove(Player);

int undoingOneStep(Element**, int**);
void playGame(int);

int getGameIdNotFinish();
void initializeNumberOfGamesSaved();
int updateNumberOfGamesSaved();
Element* saveGameStatus(Element*, char*);
void saveSettingsStatus(Player, Player, int, int, char*);
Element* saveGamePlay(Player, Player, Element*, int, int, int);
Element* loadGameStack(int);

#endif