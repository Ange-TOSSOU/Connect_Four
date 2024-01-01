#include "../include/module_grid.h"

int** initializeGrid()
{
    int **grid = (int**)calloc(ROW_GRID, sizeof(int*));
    int i;

    for(i = 0; i < ROW_GRID; ++i)
        grid[i] = (int*)calloc(COL_GRID, sizeof(int));
    
    return grid;
}

void printGrid(int **grid, Player p1, Player p2)
{
    int i, j, row, ret, l_margin = 0, n;
    CONSOLE_SCREEN_BUFFER_INFO w_size;

    ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &w_size);
    if(ret)
    {
        n = 4*COL_GRID+1;
        row = w_size.dwSize.X;
        if(row >= n)
            l_margin += (row-n)/2;
    }
    else
    {
        printf("Unable to get the console size.\n");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < ROW_GRID; ++i)
    {
        printNChar(' ', l_margin);
        for(j = 0; j < COL_GRID; ++j)
            printf("+---");
        printf("+\n");
        printNChar(' ', l_margin);
        for(j = 0; j < COL_GRID; ++j)
        {
            if(grid[i][j] == Player1)
            {
                if(strcmp(p1.color_of_piece, "yellow") == 0)
                    printf("| \033[93m%c\033[0m ", p1.type_of_piece);
                else if(strcmp(p1.color_of_piece, "blue") == 0)
                    printf("| \033[94m%c\033[0m ", p1.type_of_piece);
                else if(strcmp(p1.color_of_piece, "magenta") == 0)
                    printf("| \033[95m%c\033[0m ", p1.type_of_piece);
                else if(strcmp(p1.color_of_piece, "cyan") == 0)
                    printf("| \033[96m%c\033[0m ", p1.type_of_piece);
                else if(strcmp(p1.color_of_piece, "white") == 0)
                    printf("| \033[97m%c\033[0m ", p1.type_of_piece);
                else
                    printf("| %c ", p1.type_of_piece);
            }
            else if(grid[i][j] == Player2)
            {
                if(strcmp(p2.color_of_piece, "yellow") == 0)
                    printf("| \033[93m%c\033[0m ", p2.type_of_piece);
                else if(strcmp(p2.color_of_piece, "blue") == 0)
                    printf("| \033[94m%c\033[0m ", p2.type_of_piece);
                else if(strcmp(p2.color_of_piece, "magenta") == 0)
                    printf("| \033[95m%c\033[0m ", p2.type_of_piece);
                else if(strcmp(p2.color_of_piece, "cyan") == 0)
                    printf("| \033[96m%c\033[0m ", p2.type_of_piece);
                else if(strcmp(p2.color_of_piece, "white") == 0)
                    printf("| \033[97m%c\033[0m ", p2.type_of_piece);
                else
                    printf("| %c ", p2.type_of_piece);
            }
            else
                printf("|   ");
        }
        printf("|\n");
    }
    printNChar(' ', l_margin);
    for(j = 0; j < COL_GRID; ++j)
        printf("+---");
    printf("+\n");
    
    printNChar(' ', l_margin);
    for(j = 0; j < COL_GRID; ++j)
        printf("  %d ", j+1);
    printf("\n");
}

int** deleteGrid(int** grid)
{
    int i;

    for(i = 0; i < ROW_GRID; ++i)
        free(grid[i]);
    free(grid);
    
    return NULL;
}

int move(int** grid, int player, int move_col, Player p1, Player p2, int flag)
{
    int i, j;

    for(i = 0; i < ROW_GRID && grid[i][move_col]==None; ++i);

    if(i-1 >= 0)
    {
        for(j = 0; j < i; ++j)
        {
            grid[j][move_col] = player;
            if(flag == 1)
            {
                system("cls");
                printGrid(grid, p1, p2);
                Sleep(250);
            }
            if(j != i-1)
                grid[j][move_col] = None;
        }
        return 1;
    }

    return 0;
}

int getRowTrigger(int** grid, int col_trigger)
{
    int i;

    for(i = 0; i < ROW_GRID && grid[i][col_trigger]==None; ++i);

    return i;
}

int win_vertical(int** grid, int row_trigger, int col_trigger)
{
    int i, consecutive = 0;

    for(i = row_trigger; i < ROW_GRID; ++i)
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

int win_horizontal(int** grid, int row_trigger, int col_trigger)
{
    int j, consecutive = 0;

    for(j = col_trigger; j>=0 && grid[row_trigger][j]==grid[row_trigger][col_trigger]; --j);

    for(j = j+1; j < COL_GRID; ++j)
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

int win_diagonal_right(int** grid, int row_trigger, int col_trigger)
{
    int i, j, consecutive = 0;

    for(i = row_trigger,j = col_trigger; i<ROW_GRID && j<COL_GRID && grid[i][j]==grid[row_trigger][col_trigger]; ++i,++j);

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

int win_diagonal_left(int** grid, int row_trigger, int col_trigger)
{
    int i, j, consecutive = 0;

    for(i = row_trigger,j = col_trigger; i<ROW_GRID && j>=0 && grid[i][j]==grid[row_trigger][col_trigger]; ++i,--j);

    for(i = i-1,j = j+1; i>=0 && j < COL_GRID; --i,++j)
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

int whoWin(int** grid, int col_trigger, int nb_coups)
{
    int row_trigger = getRowTrigger(grid, col_trigger), tmp;

    tmp = win_horizontal(grid,row_trigger,col_trigger);
    if(tmp)
        return tmp;
    
    tmp = win_vertical(grid,row_trigger,col_trigger);
    if(tmp)
        return tmp;
    
    tmp = win_diagonal_right(grid,row_trigger,col_trigger);
    if(tmp)
        return tmp;
    
    tmp = win_diagonal_left(grid,row_trigger,col_trigger);
    if(tmp)
        return tmp;
    
    if(nb_coups == ROW_GRID*COL_GRID)
        return Both;
    
    return None;
}

void saveGridStatus(char* file_name, int** grid, char c)
{
    int i, j;
    FILE *f = fopen(file_name, "a+");

    for(i = 0; i < ROW_GRID; ++i)
    {
        for(j = 0; j < COL_GRID; ++j)
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

void copyGrid(int **g1, int **g2)
{
    int i, j;

    for(i = 0; i < ROW_GRID; ++i)
    {
        for(j = 0; j < COL_GRID; ++j)
            g1[i][j] = g2[i][j];
    }
}
