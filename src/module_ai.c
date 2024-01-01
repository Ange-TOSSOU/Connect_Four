#include "../include/module_ai.h"

int getMoveAIBeginner(int** grid)
{
    int i;

    do
    {
        i = (rand()%COL_GRID)+1;
    }while(grid[0][i-1] != None);

    return i;
}

int getMoveAIIntermediate(int** grid, Player p1, Player p2, int total_coup)
{
    int **g = initializeGrid(), i, stop, winner;

    for(i = 1; i <= COL_GRID; ++i)
    {
        copyGrid(g, grid);
        stop = move(g, Player1, i-1, p1, p2, 0);
        if(stop)
        {
            winner = whoWin(g, i-1, total_coup);
            if(winner == Player1)
            {
                g = deleteGrid(g);
                return i;
            }
        }
    }

    g = deleteGrid(g);
    return getMoveAIBeginner(grid);
}

int getMoveAIAdvanced(int** grid, Player p1, Player p2, int total_coup)
{
    int **g = initializeGrid(), i, stop, winner;

    for(i = 1; i <= COL_GRID; ++i)
    {
        copyGrid(g, grid);
        stop = move(g, Player1, i-1, p1, p2, 0);
        if(stop)
        {
            winner = whoWin(g, i-1, total_coup);
            if(winner == Player1)
            {
                g = deleteGrid(g);
                return i;
            }
        }
    }

    for(i = 1; i <= COL_GRID; ++i)
    {
        copyGrid(g, grid);
        stop = move(g, Player2, i-1, p1, p2, 0);
        if(stop)
        {
            winner = whoWin(g, i-1, total_coup);
            if(winner == Player2)
            {
                g = deleteGrid(g);
                return i;
            }
        }
    }

    g = deleteGrid(g);
    return getMoveAIBeginner(grid);
}
