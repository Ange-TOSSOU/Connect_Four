#include "module_grid.h"

int** initializeGrid(int row_g, int col_g)
{
    int **grid = (int**)calloc(row_g, sizeof(int*));
    int i;

    for(i = 0; i < row_g; ++i)
        grid[i] = (int*)calloc(col_g, sizeof(int));
    
    return grid;
}

void printGrid(int **grid, int row_g, int col_g)
{
    TypePieces p = getDefaultTypePieces();
    int i, j, row, ret, l_margin = 0, n;
    CONSOLE_SCREEN_BUFFER_INFO w_size;

    ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &w_size);
    if(ret)
    {
        n = 4*col_g+1;
        row = w_size.dwSize.X;
        if(row >= n)
            l_margin += (row-n)/2;
    }
    else
    {
        printf("Unable to get the console size.\n");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < row_g; ++i)
    {
        printNChar(' ', l_margin);
        for(j = 0; j < col_g; ++j)
            printf(" ---");
        printf(" \n");

        printNChar(' ', l_margin);
        for(j = 0; j < col_g; ++j)
        {
            if(grid[i][j] == Player1)
                printf("| %c ", p.player1);
            else if(grid[i][j] == Player2)
                printf("| %c ", p.player2);
            else
                printf("|   ");
        }
        printf("|\n");
    }
    printNChar(' ', l_margin);
    for(j = 0; j < col_g; ++j)
        printf(" ---");
    printf("\n");
    printNChar(' ', l_margin);
    for(j = 0; j < col_g; ++j)
        printf("  %d ", j+1);
    printf("\n");
}

int** deleteGrid(int** grid, int row_g)
{
    int i;

    for(i = 0; i < row_g; ++i)
        free(grid[i]);
    free(grid);
    
    return NULL;
}

int move(int** grid, int player, int move_col, int row)
{
    int i;

    for(i = 0; i < row && grid[i][move_col]==0; ++i);

    if(i-1 >= 0)
    {
        grid[i-1][move_col] = player;
        return 1;
    }

    return 0;
}