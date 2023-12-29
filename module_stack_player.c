#include "module_stack_player.h"


Elementp* cleanStack_Player(Elementp* stack)
{
  while(stack != NULL)
    stack = popElement_Player(stack, NULL);

  return stack;
}

Elementp* createElement_Player(Player p)
{
    Elementp* e = (Elementp*)malloc(sizeof(Elementp));
    strcpy(e->p.player_name, p.player_name);
    e->p.score = p.score;
    e->p.time = p.time;
    e->p.type_of_piece = p.type_of_piece;
    e->p.type_of_player = p.type_of_player;
    e->p.is_winner = p.is_winner;
    e->next = NULL;

  return e;
}

/*void loadGrid(Elementp* stack, int** grid)
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
}*/

Elementp* pushElement_Player(Elementp* stack, Player p)
{
  Elementp* e = createElement_Player(p);

  e->next = stack;

  return e;
}

/*Elementp* findElement(Elementp* stack, int a)
{
  while(stack != NULL)
  {
    if(stack->value == a)
      return stack;

    stack = stack->next;
  }

  return NULL;
}*/

Elementp* popElement_Player(Elementp* stack, Player* p)
{
  Elementp *cur = stack;

  if(cur != NULL)
  {
    if(p != NULL)
    {
      strcpy(p->player_name, cur->p.player_name);
      p->score = cur->p.score;
      p->time = cur->p.time;
      p->type_of_piece = cur->p.type_of_piece;
      p->type_of_player = cur->p.type_of_player;
      p->is_winner = cur->p.is_winner;
    }
    stack = cur->next;
    free(cur);
  }
  
  return stack;
}

int getNumberOfNode_Player(Elementp* stack)
{
  int cpt = 0;
  while(stack != NULL)
  {
    ++cpt;
    stack = stack->next;
  }

  return cpt;
}

/*void printStack(Elementp* stack)
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