#ifndef MODULE_AI
#define MODULE_AI

#include "module_shared.h"
#include "module_grid.h"

int getMoveAIBeginner(int**);
int getMoveAIIntermediate(int**, Player, Player, int);
int getMoveAIAdvanced(int**, Player, Player, int);

#endif