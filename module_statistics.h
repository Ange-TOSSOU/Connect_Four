#ifndef STATISTICSH
#define STATISTICSH

#include "stdio.h"
#include "stdlib.h"
#include "module_shared.h"

typedef struct
{
    int player1;
    int player2;
}Score;

void initializeScores(Score*, int, int);
void updateScores(Score*, int, int);

#endif