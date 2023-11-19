#ifndef PILEH
#define PILEH

#include <stdio.h>
#include <stdlib.h>
#include "module_shared.h"
#include "module_settings.h"
#include "module_grid.h"

struct element
{
  int grid[ROW_GRID][COL_GRID];
  TypePieces p;
  struct element *next;
};
typedef struct element Element;

Element* cleanStack(Element* stack);
Element* createElement(int**);
Element* pushElement(Element* stack);
//Element* findElement(Element* stack, int a);
Element* popElement(Element* stack, int**);

//void printStack(Element* stack);

#endif