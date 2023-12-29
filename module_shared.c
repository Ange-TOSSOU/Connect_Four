#include "module_shared.h"

void printNChar(char c, int n)
{
    int i = 0;

    while(i < n)
    {
        printf("%c", c);
        ++i;
    }
}

void printOnNChar(char *string, int n, int margin_to_add)
{
    int i = 0, j = 0, flag = 1, len = strlen(string), row, ret, l_margin = margin_to_add;
    CONSOLE_SCREEN_BUFFER_INFO w_size;

    ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &w_size);
    if(ret)
    {
        row = w_size.dwSize.X;
        if(row >= n)
            l_margin += (row-n)/2;
    }
    else
    {
        printf("Unable to get the console size.\n");
        exit(EXIT_FAILURE);
    }

    if(len == 0)
        printNChar(' ', l_margin);
    
    while(i < len)
    {
        if(flag)
        {
            printNChar(' ', l_margin);
            flag = 0;
        }
        if(j < n)
        {
            printf("%c", string[i]);
            ++j;
            ++i;
        }
        else
        {
            j = 0;
            flag = 1;
            printf("\n");
        }
    }
}

int game_not_finish(char* file_name)
{
    int n;
    FILE *f = fopen(file_name, "r");

    fscanf(f, "%d", &n);
    fclose(f);

    if(n == None)
        return 1;

    return 0;
}

int getNumberOfGamesSaved()
{
    int n = 0;
    FILE *f = fopen(FILE_NAME_NUMBER_OF_GAMES_SAVED, "r");

    if(f != NULL)
    {
        fscanf(f, "%d", &n);
        fclose(f);
    }
    
    return n;
}

int loadPlayers(Player* p1, Player* p2, int game_id)
{
    char file_name_s[ROW_TEXT+1] = FILE_NAME_SAVE_SETTINGS, num[3] = "";
    int a, turn;
    FILE *f = NULL;

    itoa(game_id, num, 10);
    strcat(file_name_s, num);
    strcat(file_name_s, ".txt");

    f = fopen(file_name_s, "r");

    fscanf(f, "%d", &a);
    if(a == Player1)
    {
        p1->is_winner = 1;
        p2->is_winner = 0;
    }
    else if(a == Player2)
    {
        p1->is_winner = 0;
        p2->is_winner = 1;
    }
    else if(a == Both)
    {
        p1->is_winner = Both;
        p2->is_winner = Both;
    }
    else
    {
        p1->is_winner = -1;
        p2->is_winner = -1;
    }
    fscanf(f, "%d %d", &(p1->score), &(p2->score));
    fscanf(f, "%ld %ld", &(p1->time), &(p2->time));
    fscanf(f, "%d", &turn);
    fscanf(f, "%d %d", &(p1->type_of_player), &(p2->type_of_player));
    fgetc(f);
    fgets(p1->player_name, ROW_TEXT+2, f);
    if(p1->player_name[strlen(p1->player_name)-1] == '\n')
        p1->player_name[strlen(p1->player_name)-1] = '\0';
    fgets(p2->player_name, ROW_TEXT+2, f);
    if(p2->player_name[strlen(p2->player_name)-1] == '\n')
        p2->player_name[strlen(p2->player_name)-1] = '\0';
    p1->type_of_piece = fgetc(f);
    fgetc(f);
    p2->type_of_piece = fgetc(f);

    fclose(f);

    return turn;
}