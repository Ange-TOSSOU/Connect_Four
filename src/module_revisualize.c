#include "../include/module_revisualize.h"

int getGameIdFinish()
{
    char file_name_g[ROW_TEXT+1] = "", file_name_s[ROW_TEXT+1] = "", num[3] = "", message[ROW_TEXT+1] = "";
    int lim = getNumberOfGamesSaved(), c, i, j, n, *tab;
    Player p1, p2;

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
            loadPlayers(&p1, &p2, i);
            n = getTypeOfPlayer2(file_name_s);
            itoa(j+1, message, 10);
            strcat(message, " - View the file : ");
            strcat(message, p1.player_name);
            strcat(message, " vs ");
            strcat(message, p2.player_name);
            if(n == AI_Advanced)
                strcat(message, " (Advanced)");
            else if(n == AI_Intermediate)
                strcat(message, " (Intermediate)");
            else if(n == AI_Beginner)
                strcat(message, " (Beginner)");
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
    printf("\n\n");

    c = 0;
    while(!(1<=c && c<=j+1))
        c = get_choice();
    
    if(c < j+1) /* If the player want to load a game */
        c = tab[c-1];
    else /* If c==j+1 ie the player want to exit */
        c = -1;

    free(tab);

    return c;
}

void viewGame()
{
    char file_name_g[ROW_TEXT+1] = FILE_NAME_SAVE_PLAY, num[3] = "", tmp[ROW_TEXT] = "", c = '\n';
    int **g = initializeGrid() ,**grid = initializeGrid(), i, j, k, l, move_col, a, player_turn = Player1, game_id, start = 1;
    Player p1, p2;
    FILE *f = NULL;

    game_id = getGameIdFinish();
    if(game_id == 0)
    {
        printOnNChar("No complete game found !", ROW_TEXT, 0);
        printf("\n");
        printOnNChar("Press enter key to go back to the menu : ", ROW_TEXT, 0);
        while(getchar() != '\n');
    }
    else
    {
        welcome("* LOADING THE GAME VIEW *", "DONE");
        loadPlayers(&p1, &p2, game_id);
        system("cls");
        printPlayersInfo(p1, p2);
        printf("\n\n");
        printOnNChar("Press enter key to view the game : ", ROW_TEXT, 0);
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
                    if(start)
                    {
                        copyGrid(g, grid);
                        start = 0;
                    }
                    else
                    {
                        system("cls");
                        if(player_turn == Player1)
                            strcpy(tmp, p1.player_name);
                        else
                            strcpy(tmp, p2.player_name);
                        strcat(tmp, " move.");
                        printOnNChar(tmp, ROW_TEXT, 0);
                        printf("\n");
                        Sleep(1000);
                        for(k=0; k<ROW_GRID; ++k)
                        {
                            for(l=0; l<COL_GRID; ++l)
                            {
                                if(g[k][l] != grid[k][l])
                                {
                                    move_col = l;
                                    l = COL_GRID;
                                    k = ROW_GRID;
                                }
                            }
                        }
                        move(g, player_turn, move_col, p1, p2, 1);
                        Sleep(500);
                        if(player_turn == Player1)
                            player_turn = Player2;
                        else
                            player_turn = Player1;
                        copyGrid(g, grid);
                    }
                    c = fgetc(f);
                }
            }
        }

        printf("\n\n");
        printOnNChar("END OF THE GAME !", ROW_TEXT, 0);
        printf("\n\n");
        printPlayersInfo(p1, p2);
        printf("\n\n");
        printOnNChar("Press enter key to go back to the menu : ", ROW_TEXT, 0);
        while(getchar() != '\n');
    
        deleteGrid(grid);
        fclose(f);
    }
}