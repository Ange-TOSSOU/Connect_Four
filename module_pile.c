#include "module_pile.h"


Element* cleanStack(Element* stack)
{
  while(stack != NULL)
    stack = popElement(stack);

  return stack;
}

Element* createElement(int** grid)
{
    int i, j;
    Element* e = (Element*)malloc(sizeof(Element));
    for(i = 0; i < ROW_GRID; ++i)
    {
        for(j = 0; j < COL_GRID; ++j)
            e->grid[i][j] = grid[i][j];
    }
    e->p = getDefaultTypePieces();
    e->next = NULL;

  return e;
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

Element* popElement(Element* stack)
{
  Element *cur = stack;

  if(cur != NULL)
  {
    stack = cur->next;
    free(cur);
  }
  
  return stack;
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