#ifndef PILEH
#define PILEH

#include <stdio.h>
#include <stdlib.h>
#include "module_shared.h"
#include "module_settings.h"
#include "module_grid.h"

struct element
{
  int **grid;
  TypePieces p;
  struct element *next;
};
typedef struct element Element;

Element* cleanStack(Element*);
Element* createElement(int**);
Element* pushElement(Element*, int**);
//Element* findElement(Element* stack, int a);
Element* popElement(Element*, int**);
void loadGrid(Element*, int**);
int getNumberOfNode(Element*);

//void printStack(Element* stack);

#endif