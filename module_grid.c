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
            printf("+---");
        printf("+\n");

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
        printf("+---");
    printf("+\n");
    
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

int move(int** grid, int player, int move_col, int row_g)
{
    int i;

    for(i = 0; i < row_g && grid[i][move_col]==None; ++i);

    if(i-1 >= 0)
    {
        grid[i-1][move_col] = player;
        return 1;
    }

    return 0;
}

int getRowTrigger(int** grid, int col_trigger, int row_g)
{
    int i;

    for(i = 0; i < row_g && grid[i][col_trigger]==None; ++i);

    return i;
}

int win_vertical(int** grid, int row_trigger, int col_trigger, int row_g)
{
    int i, consecutive = 0;

    for(i = row_trigger; i < row_g; ++i)
    {
        if(grid[i][col_trigger] == grid[row_trigger][col_trigger])
            ++consecutive;
        else
            break;
    }

    if(consecutive == 4)
        return grid[row_trigger][col_trigger];
    
    return None;
}

int win_horizontal(int** grid, int row_trigger, int col_trigger, int col_g)
{
    int j, consecutive = 0;

    for(j = col_trigger; j>=0 && grid[row_trigger][j]==grid[row_trigger][col_trigger]; --j);

    for(j = j+1; j < col_g; ++j)
    {
        if(grid[row_trigger][j] == grid[row_trigger][col_trigger])
            ++consecutive;
        else
            break;
    }

    if(consecutive == 4)
        return grid[row_trigger][col_trigger];
    
    return None;
}

int win_diagonal_right(int** grid, int row_trigger, int col_trigger, int row_g, int col_g)
{
    int i, j, consecutive = 0;

    for(i = row_trigger,j = col_trigger; i<row_g && j<col_g && grid[i][j]==grid[row_trigger][col_trigger]; ++i,++j);

    for(i = i-1,j = j-1; i>=0 && j>=0; --i,--j)
    {
        if(grid[i][j] == grid[row_trigger][col_trigger])
            ++consecutive;
        else
            break;
    }

    if(consecutive == 4)
        return grid[row_trigger][col_trigger];
    
    return None;
}

int win_diagonal_left(int** grid, int row_trigger, int col_trigger, int row_g, int col_g)
{
    int i, j, consecutive = 0;

    for(i = row_trigger,j = col_trigger; i<row_g && j>=0 && grid[i][j]==grid[row_trigger][col_trigger]; ++i,--j);

    for(i = i-1,j = j+1; i>=0 && j < col_g; --i,++j)
    {
        if(grid[i][j] == grid[row_trigger][col_trigger])
            ++consecutive;
        else
            break;
    }

    if(consecutive == 4)
        return grid[row_trigger][col_trigger];
    
    return None;
}

int whoWin(int** grid, int col_trigger, int row_g, int col_g, int nb_coups)
{
    int row_trigger = getRowTrigger(grid, col_trigger, row_g), tmp;

    tmp = win_horizontal(grid,row_trigger,col_trigger,col_g);
    if(tmp)
        return tmp;
    
    tmp = win_vertical(grid,row_trigger,col_trigger,row_g);
    if(tmp)
        return tmp;
    
    tmp = win_diagonal_right(grid,row_trigger,col_trigger,row_g,col_g);
    if(tmp)
        return tmp;
    
    tmp = win_diagonal_left(grid,row_trigger,col_trigger,row_g,col_g);
    if(tmp)
        return tmp;
    
    if(nb_coups == row_g*col_g)
        return Both;
    
    return None;
}

void saveGridStatus(char* file_name, int** grid, int row_g, int col_g, char c)
{
    int i, j;
    FILE *f = fopen(file_name, "w");

    for(i = 0; i < row_g; ++i)
    {
        for(j = 0; j < col_g; ++j)
        {
            if(i == 0 && j == 0)
                fprintf(f, "%d", grid[i][j]);
            else
                fprintf(f, " %d", grid[i][j]);
        }
    }

    if(c == '\n')
        fprintf(f, "%c", c);

    fclose(f);
}