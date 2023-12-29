#include "module_revisualize.h"

int getGameIdFinish()
{
    char file_name_g[ROW_TEXT+1] = "", file_name_s[ROW_TEXT+1] = "", num[3] = "", message[ROW_TEXT+1] = "";
    int lim = getNumberOfGamesSaved(), c, i, j, *tab;

    tab = calloc(lim, sizeof(int));

    for(i = 1, j = 0; i <= lim; ++i)
    {
        strcpy(file_name_g, FILE_NAME_SAVE_PLAY);
        strcpy(file_name_s, FILE_NAME_SAVE_SETTINGS);
        strcpy(message, "");
        itoa(i, num, 10);
        strcat(file_name_g, num);
        strcat(file_name_g, ".txt");
        strcat(file_name_s, num);
        strcat(file_name_s, ".txt");

        if(exist(file_name_g) && exist(file_name_s) && !game_not_finish(file_name_s))
        {
            itoa(j+1, message, 10);
            strcat(message, " - View the file : ");
            strcat(message, file_name_g);
            printOnNChar(message, ROW_TEXT, 0);
            printf("\n");
            tab[j] = i;
            ++j;
        }
    }

    if(j == 0)
        return 0;
    
    ++j;
    strcpy(message, "");
    itoa(j, message, 10);
    strcat(message, " - Exit");
    printOnNChar(message, ROW_TEXT, 0);
    printf("\n");

    c = 0;
    while(!(1<=c && c<=j))
        c = get_choice();

    c = tab[c-1];

    free(tab);

    return c;
}

void printPlayersInfo(Player p1, Player p2)
{
    char tmp[ROW_TEXT+1] = "";
    int len;

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
    strcpy(tmp, "Type of pieces : ");
    len = strlen(tmp);
    tmp[len] = p1.type_of_piece;
    tmp[len+1] = '\0';
    printOnNChar(tmp, ROW_TEXT, 4);
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
    strcpy(tmp, "Type of pieces : ");
    len = strlen(tmp);
    tmp[len] = p2.type_of_piece;
    tmp[len+1] = '\0';
    printOnNChar(tmp, ROW_TEXT, 4);
    printf("\n\n");

    if(p1.score < p2.score)
    {
        strcpy(tmp, "Winner : ");
        strcat(tmp, p1.player_name);
        printOnNChar(tmp, ROW_TEXT, 0);
        printf("\n");
    }
    else if(p2.score < p1.score)
    {
        strcpy(tmp, "Winner : ");
        strcat(tmp, p2.player_name);
        printOnNChar(tmp, ROW_TEXT, 0);
        printf("\n");
    }
    else
    {
        printOnNChar("Winner : Draw", ROW_TEXT, 0);
        printf("\n");
    }
}

void viewGame()
{
    char file_name_g[ROW_TEXT+1] = FILE_NAME_SAVE_PLAY, num[3] = "", tmp[ROW_TEXT] = "", c = '\n';
    int **grid = initializeGrid(), i, j, a, n = 0, player_turn = Player1, game_id;
    Player p1, p2;
    FILE *f = NULL;

    game_id = getGameIdFinish();
    if(game_id == 0)
    {
        printOnNChar("No complete game found !", ROW_TEXT, 0);
        printf("\n");
        printOnNChar("Press any key to exit ... ", ROW_TEXT, 0);
        while(getchar() != '\n');
    }
    else
    {
        loadPlayers(&p1, &p2, game_id);
        system("cls");
        printPlayersInfo(p1, p2);
        printf("\n\n");
        printOnNChar("Press any key to view the game ... ", ROW_TEXT, 0);
        while(getchar() != '\n');

        itoa(game_id, num, 10);
        strcat(file_name_g, num);
        strcat(file_name_g, ".txt");

        f = fopen(file_name_g, "r");

        i = j = 0;
        while(c != EOF)
        {
            fscanf(f, "%d", &a);
            grid[i][j] = a;
            ++j;
            if(j == COL_GRID)
            {
                j = 0;
                ++i;
                if(i == ROW_GRID)
                {
                    i = 0;
                    ++n;
                    system("cls");
                    if(player_turn == Player1)
                        strcpy(tmp, p1.player_name);
                    else
                        strcpy(tmp, p2.player_name);
                    strcat(tmp, " move.");
                    printOnNChar(tmp, ROW_TEXT, 0);
                    printf("\n");
                    printGrid(grid);
                    Sleep(1000);
                    if(player_turn == Player1)
                        player_turn = Player2;
                    else
                        player_turn = Player1;
                    c = fgetc(f);
                }
            }
        }

        printf("\n\n");
        printOnNChar("END OF THE GAME !", ROW_TEXT, 0);
        printf("\n\n");
        printOnNChar("Press any key to exit ... ", ROW_TEXT, 0);
        while(getchar() != '\n');
    
        deleteGrid(grid);
        fclose(f);
    }
}