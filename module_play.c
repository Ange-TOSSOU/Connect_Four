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
    copyHead(*game_stack, grid);

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

Element* saveGamePlay(Player p1, Player p2, Element* game_stack, int row_g, int col_g, int game_id, int winner, int player_turn)
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
    return saveGameStatus(game_stack, row_g, col_g, file_name_g);
}

Element* saveGameStatus(Element* game_stack, int row_g, int col_g, char* file_name)
{
    int **tmp = initializeGrid(row_g, col_g);
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
            saveGridStatus(file_name, tmp, row_g, col_g, '\0');
        else
            saveGridStatus(file_name, tmp, row_g, col_g, '\n');
    }

    tmp = deleteGrid(tmp, row_g);

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

int getGameId()
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
    
    strcpy(message, "");
    itoa(j+1, message, 10);
    strcat(message, " - New game");
    printOnNChar(message, ROW_TEXT, 0);
    printf("\n");

    c = 0;
    while(!(1<=c && c<=j))
        c = get_choice();
    
    c = tab[c-1];

    free(tab);
    return c;
}

Element* loadGameStack(int row_g, int col_g, int game_id)
{
    char file_name_g[ROW_TEXT+1] = "", num[3] = "";
    int **grid = initializeGrid(row_g, col_g), i, j, a;
    Element* stack = NULL;
    FILE *f = NULL;

    itoa(game_id, num, 10);
    strcat(file_name_g, num);
    strcat(file_name_g, ".txt");

    f = fopen(file_name_g, "r");

    i = j = 0;
    while(fscanf(f, "%d", &a))
    {
        grid[i][j] = a;
        ++j;
        if(j == col_g-1)
        {
            if(i == row_g-1)
            {
                i = j = 0;
                stack = pushElement(stack, grid);
            }
            else
            {
                j = 0;
                ++i;
            }
        }
    }
    
    deleteGrid(grid, row_g);
    fclose(f);

    return stack;
}

void loadGrid(Element* game_stack, int** grid, int row_g, int col_g)
{
    int i, j;

    for(i = 0; i < row_g; ++i)
    {
        for(j = 0; j < col_g; ++j)
            grid[i][j] = game_stack->grid[i][j];
    }
}

int loadPlayers(Player* p1, Player* p2, int game_id)
{
    char file_name_s[ROW_TEXT+1] = "", num[3] = "";
    int a, turn;
    FILE *f = NULL;

    itoa(game_id, num, 10);
    strcat(file_name_s, num);
    strcat(file_name_s, ".txt");

    f = fopen(file_name_s, "r");

    fscanf(f, "%d", &a);
    fscanf(f, "%d %d", &(p1->score), &(p2->score));
    fscanf(f, "%d", &turn);
    fscanf(f, "%d %d", &(p1->type_of_player), &(p2->type_of_player));
    fgets(p1->player_name, ROW_TEXT+2, f);
    if(p1->player_name[strlen(p1->player_name)-1] == '\n')
        p1->player_name[strlen(p1->player_name)-1] = '\0';
    fgets(p2->player_name, ROW_TEXT+2, f);
    if(p2->player_name[strlen(p2->player_name)-1] == '\n')
        p2->player_name[strlen(p2->player_name)-1] = '\0';

    fclose(f);

    return turn;
}

void playGame(int row_g, int col_g, int player2_type)
{
    char his_move;
    int someone_win, player_turn, stop, game_id, total_coup = 0;
    Element* game_stack = NULL;

    game_id = getGameId();
    if(game_id == 0)
    {
        grid = initializeGrid(row_g, col_g);
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
        game_stack = loadGameStack(row_g, col_g, game_id);
        loadGrid(game_stack, grid, row_g, col_g);
        player_turn = loadPlayers(&p1, &p2, game_id);
    }

    someone_win = None;
    while(!someone_win)
    {
        system("cls");
        printGrid(grid, row_g, col_g);
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
                stop = move(grid, player_turn, his_move-'0' -1, ROW_GRID);

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
            someone_win = whoWin(grid, his_move-'0' -1, row_g, col_g, total_coup);
    }

    if(someone_win == QuitGame)
        someone_win = None;
    game_stack = saveGamePlay(p1, p2, game_stack, row_g, col_g, game_id, someone_win, player_turn);

    grid = deleteGrid(grid, row_g);
}