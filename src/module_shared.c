#include "../include/module_shared.h"

int get_choice()
{
    int c, flag = 0;
    
    while(flag != 1)
    {
        printOnNChar("Make a choice : ", ROW_TEXT, 0);
        flag = scanf("%d", &c);
        while(getchar() != '\n');
    }

    return c;
}

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

int getTypeOfPlayer2(char* file_name)
{
    char tmp[N_CONFS+1];
    int tp2 = AI_Beginner, i;
    FILE *f = fopen(file_name, "r");

    fseek(f, 0, SEEK_SET);
    for(i = 0; i < 4; ++i)
        fgets(tmp, N_CONFS+1, f);

    fscanf(f, "%d", &tp2);
    fscanf(f, "%d", &tp2);

    fclose(f);

    return tp2;
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
    char file_name_s[N_CONFS +1] = FILE_NAME_SAVE_SETTINGS, num[3] = "";
    int a, turn;
    FILE *f = NULL;

    itoa(game_id, num, 10);
    strcat(file_name_s, num);
    strcat(file_name_s, ".txt");

    f = fopen(file_name_s, "r");

    fseek(f, 0, SEEK_SET);
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
    fgetc(f);
    fscanf(f, "%s", p1->color_of_piece);
    fscanf(f, "%s", p2->color_of_piece);

    fclose(f);

    return turn;
}

void printPlayersInfo(Player p1, Player p2)
{
    char tmp[ROW_TEXT+1] = "";

    printOnNChar("Player 1", ROW_TEXT, 0);
    printf("\n");
    strcpy(tmp, "Name : ");
    strcat(tmp, p1.player_name);
    printOnNChar(tmp, ROW_TEXT, 4);
    printf("\n");
    strcpy(tmp, "Type of player : ");
    if(p1.type_of_player == Human)
        strcat(tmp, "Human");
    else
        strcat(tmp, "AI");
    printOnNChar(tmp, ROW_TEXT, 4);
    printf("\n");
    printOnNChar("Type of pieces : ", ROW_TEXT, 4);
    if(strcmp(p1.color_of_piece, "yellow") == 0)
        printf("\033[93m%c\033[0m", p1.type_of_piece);
    else if(strcmp(p1.color_of_piece, "blue") == 0)
        printf("\033[94m%c\033[0m", p1.type_of_piece);
    else if(strcmp(p1.color_of_piece, "magenta") == 0)
        printf("\033[95m%c\033[0m", p1.type_of_piece);
    else if(strcmp(p1.color_of_piece, "cyan") == 0)
        printf("\033[96m%c\033[0m", p1.type_of_piece);
    else if(strcmp(p1.color_of_piece, "white") == 0)
        printf("\033[97m%c\033[0m", p1.type_of_piece);
    else
        printf("%c", p1.type_of_piece);
    printf("\n\n");

    printOnNChar("Player 2", ROW_TEXT, 0);
    printf("\n");
    strcpy(tmp, "Name : ");
    strcat(tmp, p2.player_name);
    printOnNChar(tmp, ROW_TEXT, 4);
    printf("\n");
    strcpy(tmp, "Type of player : ");
    if(p2.type_of_player == Human)
        strcat(tmp, "Human");
    else
        strcat(tmp, "AI");
    printOnNChar(tmp, ROW_TEXT, 4);
    printf("\n");
    printOnNChar("Type of pieces : ", ROW_TEXT, 4);
    if(strcmp(p2.color_of_piece, "yellow") == 0)
        printf("\033[93m%c\033[0m", p2.type_of_piece);
    else if(strcmp(p2.color_of_piece, "blue") == 0)
        printf("\033[94m%c\033[0m", p2.type_of_piece);
    else if(strcmp(p2.color_of_piece, "magenta") == 0)
        printf("\033[95m%c\033[0m", p2.type_of_piece);
    else if(strcmp(p2.color_of_piece, "cyan") == 0)
        printf("\033[96m%c\033[0m", p2.type_of_piece);
    else if(strcmp(p2.color_of_piece, "white") == 0)
        printf("\033[97m%c\033[0m", p2.type_of_piece);
    else
        printf("%c", p2.type_of_piece);
    printf("\n\n");

    if(p1.is_winner==1 && p2.is_winner==0)
    {
        strcpy(tmp, "Winner : ");
        strcat(tmp, p1.player_name);
        printOnNChar(tmp, ROW_TEXT, 0);
        printf("\n");
    }
    else if(p1.is_winner==0 && p2.is_winner==1)
    {
        strcpy(tmp, "Winner : ");
        strcat(tmp, p2.player_name);
        printOnNChar(tmp, ROW_TEXT, 0);
        printf("\n");
    }
    else if(p1.is_winner==Both && p2.is_winner==Both)
    {
        printOnNChar("Winner : Draw", ROW_TEXT, 0);
        printf("\n");
    }
    /*if(p1.score < p2.score)
    {
        strcpy(tmp, "Winner : ");
        strcat(tmp, p2.player_name);
        printOnNChar(tmp, ROW_TEXT, 0);
        printf("\n");
    }
    else if(p2.score < p1.score)
    {
        strcpy(tmp, "Winner : ");
        strcat(tmp, p1.player_name);
        printOnNChar(tmp, ROW_TEXT, 0);
        printf("\n");
    }
    else
    {
        printOnNChar("Winner : Draw", ROW_TEXT, 0);
        printf("\n");
    }*/
}
