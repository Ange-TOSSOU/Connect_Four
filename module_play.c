#include "module_play.h"

void initializePlayersHuman(Player* p, int num)
{
    char tmp[ROW_TEXT+2] = "";
    int n;

    strcat(tmp, "Player ");
    n = strlen(tmp);
    tmp[n-1] = '0' + (num+3)/2;
    tmp[n] = '\0';
    strcat(tmp, ", give your name : ");
    printOnNChar(tmp, ROW_TEXT, 0);
    fgets(p->player_name, ROW_TEXT+2, stdin);
    n = strlen(p->player_name);
    if(p->player_name[n-1] == '\n')
        p->player_name[n-1] = 0;
    else
        while(getchar() != '\n');
    
    p->type_of_player = Human;
    p->score = (ROW_GRID*COL_GRID)/2 + 4;
}

void initializePlayersAI(Player* p, int num)
{
    char tmp[ROW_TEXT+2] = "";
    int n;
    
    strcat(tmp, "Player ");
    n = strlen(tmp);
    tmp[n-1] = '0' + (num+3)/2;
    tmp[n] = '\0';
    strcat(tmp, " is AI.");
    printOnNChar(tmp, ROW_TEXT, 0);
    printf("\n");

    strcpy(p->player_name, "AI");
    p->type_of_player = AI;
    p->score = (ROW_GRID*COL_GRID)/2 + 4;
}

char getMove(Player p)
{
    char tmp[ROW_TEXT+1] = "", c = 0;

    strcat(tmp, p.player_name);
    strcat(tmp, ", make a move : ");

    while(!( ('1'<=c && c<='7') || c=='u' || c=='q'))
    {
        printOnNChar(tmp, ROW_TEXT, 0);
        c = getchar();
        while(getchar() != '\n');
    }

    return c;
}

int undoingOneStep(Element** game_stack, int** grid)
{
    int n = getNumberOfNode(*game_stack);

    if(n < 3)
        return 0;

    *game_stack = popElement(*game_stack, NULL);
    *game_stack = popElement(*game_stack, NULL);
    loadGrid(*game_stack, grid);

    return 1;
}

void initializeNumberOfGamesSaved()
{
    FILE *f = NULL;

    if(!exist(FILE_NAME_NUMBER_OF_GAMES_SAVED))
    {
        f = fopen(FILE_NAME_NUMBER_OF_GAMES_SAVED, "a+");
        fprintf(f, "0");
        fclose(f);
    }
}

int updateNumberOfGamesSaved()
{
    int n = 0;
    FILE *f = NULL;
    
    if(!exist(FILE_NAME_NUMBER_OF_GAMES_SAVED))
        initializeNumberOfGamesSaved();
    
    n = 1 + getNumberOfGamesSaved();
    f = fopen(FILE_NAME_NUMBER_OF_GAMES_SAVED, "w");
    fprintf(f, "%d", n);
    fclose(f);

    return n;
}

Element* saveGamePlay(Player p1, Player p2, Element* game_stack, int game_id, int winner, int player_turn)
{
    char file_name_g[ROW_TEXT+1] = FILE_NAME_SAVE_PLAY, file_name_s[ROW_TEXT+1] = FILE_NAME_SAVE_SETTINGS, num[3] = "";

    if(game_id == 0)
        game_id = updateNumberOfGamesSaved();
    
    itoa(game_id, num, 10);
    strcat(file_name_g, num);
    strcat(file_name_g, ".txt");
    strcat(file_name_s, num);
    strcat(file_name_s, ".txt");

    if(exist(file_name_g))
        remove(file_name_g);
    if(exist(file_name_s))
        remove(file_name_s);

    saveSettingsStatus(p1, p2, winner, player_turn, file_name_s);
    return saveGameStatus(game_stack, file_name_g);
}

Element* saveGameStatus(Element* game_stack, char* file_name)
{
    int **tmp = initializeGrid();
    Element *reverse_stack = NULL;

    while(game_stack != NULL)
    {
        game_stack = popElement(game_stack, tmp);
        reverse_stack = pushElement(reverse_stack, tmp);
    }

    while(reverse_stack != NULL)
    {
        reverse_stack = popElement(reverse_stack, tmp);
        if(reverse_stack == NULL)
            saveGridStatus(file_name, tmp, '\0');
        else
            saveGridStatus(file_name, tmp, '\n');
    }

    tmp = deleteGrid(tmp);

    return game_stack;
}

void saveSettingsStatus(Player p1, Player p2, int winner, int player_turn, char* file_name)
{
    TypePieces p = getDefaultTypePieces();
    FILE *f = fopen(file_name, "a+");

    fprintf(f, "%d\n", winner);
    fprintf(f, "%d %d\n", p1.score, p2.score);
    fprintf(f, "%d\n", player_turn);
    fprintf(f, "%d %d\n", p1.type_of_player, p2.type_of_player);
    fprintf(f, "%s\n", p1.player_name);
    fprintf(f, "%s\n", p2.player_name);
    fprintf(f, "%c %c", p.player1, p.player2);

    fclose(f);
}

int getGameIdNotFinish()
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

        if(exist(file_name_g) && exist(file_name_s) && game_not_finish(file_name_s))
        {
            itoa(j+1, message, 10);
            strcat(message, " - Load the file : ");
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
    strcat(message, " - New game");
    printOnNChar(message, ROW_TEXT, 0);
    printf("\n");
    strcpy(message, "");
    itoa(j+1, message, 10);
    strcat(message, " - Exit");
    printOnNChar(message, ROW_TEXT, 0);
    printf("\n");

    c = 0;
    while(!(1<=c && c<=j+1))
        c = get_choice();
    
    if(c < j+1)
        c = tab[c-1];
    else
        c = -1;

    free(tab);

    return c;
}

Element* loadGameStack(int game_id)
{
    char file_name_g[ROW_TEXT+1] = FILE_NAME_SAVE_PLAY, num[3] = "", c = '\n';
    int **grid = initializeGrid(), i, j, a, n = 0;
    Element* stack = NULL;
    FILE *f = NULL;

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
                stack = pushElement(stack, grid);
                c = fgetc(f);
            }
        }
    }
    
    deleteGrid(grid);
    fclose(f);

    return stack;
}

/*void loadGrid(Element* game_stack, int** grid, int row_g, int col_g)
{
    int i, j;

    for(i = 0; i < row_g; ++i)
    {
        for(j = 0; j < col_g; ++j)
            grid[i][j] = game_stack->grid[i][j];
    }
}*/

void playGame(int player2_type)
{
    char his_move;
    int someone_win, player_turn, stop, game_id, total_coup = 0;
    int **grid;
    Player p1, p2;
    Element* game_stack = NULL;

    grid = initializeGrid();

    game_id = getGameIdNotFinish();
    if(game_id == -1)
        return;
    else if(game_id == 0)
    {
        game_stack = pushElement(game_stack, grid);
        initializePlayersHuman(&p1, Player1);
        if(player2_type == Human)
            initializePlayersHuman(&p2, Player2);
        else
            initializePlayersAI(&p2, Player2);
        player_turn = Player1;
    }
    else
    {
        game_stack = loadGameStack(game_id);
        loadGrid(game_stack, grid);
        player_turn = loadPlayers(&p1, &p2, game_id);
    }

    someone_win = None;
    while(!someone_win)
    {
        system("cls");
        printGrid(grid);
        printf("\n");
        
        stop = 0;
        while(!stop)
        {
            if(player_turn == Player1)
                his_move = getMove(p1);
            else
                his_move = getMove(p2);
            
            if(his_move == 'u')
            {
                if(undoingOneStep(&game_stack, grid))
                {
                    total_coup -= 2;
                    ++p1.score;
                    ++p2.score;
                    stop = 1;
                }
                else
                    stop = 0;
            }
            else if(his_move == 'q')
            {
                someone_win = QuitGame;
                stop = 1;
            }
            else if('1'<=his_move && his_move<='7')
            {
                stop = move(grid, player_turn, his_move-'0' -1);

                if(stop)
                {
                    ++total_coup;
                    game_stack = pushElement(game_stack, grid);

                    if(player_turn == Player1)
                    {
                        --p1.score;
                        player_turn = Player2;
                    }
                    else
                    {
                        --p2.score;
                        player_turn = Player1;
                    }
                }
            }
            else
                exit(EXIT_FAILURE);
        }

        if(someone_win!=QuitGame && '1'<=his_move && his_move<='7')
            someone_win = whoWin(grid, his_move-'0' -1, total_coup);
        
        if(someone_win == Player1)
            p2.score = 0;
        if(someone_win == Player2)
            p1.score = 0;
    }

    if(someone_win == QuitGame)
        someone_win = None;
    game_stack = saveGamePlay(p1, p2, game_stack, game_id, someone_win, player_turn);

    grid = deleteGrid(grid);
}