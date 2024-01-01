#ifndef PILE_PLAYER_H
#define PILE_PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "module_shared.h"
#include "module_settings.h"
#include "module_grid.h"

struct elementp
{
  Player p;
  struct elementp *next;
};
typedef struct elementp Elementp;

Elementp* cleanStack_Player(Elementp*);
Elementp* createElement_Player(Player);
Elementp* pushElement_Player(Elementp*, Player);
//Elementp* findElement(Elementp* stack, int a);
Elementp* popElement_Player(Elementp*, Player*);
//void loadGrid(Elementp*, int**);
int getNumberOfNode_Player(Elementp*);

//void printStack(Elementp* stack);

#endif