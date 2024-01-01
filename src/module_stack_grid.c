#include "../include/module_stack_grid.h"


Element* cleanStack(Element* stack)
{
  while(stack != NULL)
    stack = popElement(stack, NULL);

  return stack;
}

Element* createElement(int** grid)
{
    int i, j;
    Element* e = (Element*)malloc(sizeof(Element));
    e->grid = initializeGrid();
    for(i = 0; i < ROW_GRID; ++i)
    {
        for(j = 0; j < COL_GRID; ++j)
            e->grid[i][j] = grid[i][j];
    }
    e->p = getDefaultTypePieces();
    e->next = NULL;

  return e;
}

void loadGrid(Element* stack, int** grid)
{
  int i, j;
  
  if(stack != NULL)
  {
    for(i = 0; i < ROW_GRID; ++i)
    {
        for(j = 0; j < COL_GRID; ++j)
            grid[i][j] = stack->grid[i][j];
    }
  }
}

Element* pushElement(Element* stack, int** grid)
{
  Element* e = createElement(grid);

  e->next = stack;

  return e;
}

/*Element* findElement(Element* stack, int a)
{
  while(stack != NULL)
  {
    if(stack->value == a)
      return stack;

    stack = stack->next;
  }

  return NULL;
}*/

Element* popElement(Element* stack, int** a)
{
  int i, j;
  Element *cur = stack;

  if(cur != NULL)
  {
    if(a != NULL)
    {
      for(i = 0; i < ROW_GRID; ++i)
      {
        for(j = 0; j < COL_GRID; ++j)
          a[i][j] = cur->grid[i][j];
      }
    }
    stack = cur->next;
    deleteGrid(cur->grid);
    free(cur);
  }
  
  return stack;
}

int getNumberOfNode(Element* stack)
{
  int cpt = 0;
  while(stack != NULL)
  {
    ++cpt;
    stack = stack->next;
  }

  return cpt;
}

/*void printStack(Element* stack)
{
  int start = 1;
  
  while(stack != NULL)
  {
    if(start)
    {
      printf("{%d}", stack->value);
      start = 0;
    }
    else
      printf(" -> {%d}", stack->value);

    stack = stack->next;
  }

  if(start)
    printf("The stack is empty.");

  printf("\n");
}*/