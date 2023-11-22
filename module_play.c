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

Element* saveGamePlay(Player p1, Player p2, Element* game_stack, int row_g, int col_g, int game_id, int winner, Score sc)
{
    char file_name_g[ROW_TEXT+1] = FILE_NAME_SAVE_PLAY, file_name_s[ROW_TEXT+1] = FILE_NAME_SAVE_SETTINGS, num[3] = "";
    int **tmp = initializeGrid(row_g, col_g);
    Element *reverse_stack = NULL;

    while(game_stack != NULL)
    {
        game_stack = popElement(game_stack, tmp);
        reverse_stack = pushElement(reverse_stack, tmp);
    }

    if(game_id == 0)
        game_id = updateNumberOfGamesSaved();
    
    itoa(game_id, num, 10);
    strcat(file_name_g, num);
    strcat(file_name_g, ".txt");
    strcat(file_name_s, num);
    strcat(file_name_s, ".txt");

    saveSettingsStatus(p1, p2, winner, sc, file_name_s);

    while(reverse_stack != NULL)
    {
        reverse_stack = popElement(reverse_stack, tmp);
        if(reverse_stack == NULL)
            saveGridStatus(file_name_g, tmp, row_g, col_g, '\0');
        else
            saveGridStatus(file_name_g, tmp, row_g, col_g, '\n');
    }

    tmp = deleteGrid(tmp, row_g);

    return game_stack;
}

void saveSettingsStatus(Player p1, Player p2, int winner, Score sc, char* file_name)
{
    TypePieces p = getDefaultTypePieces();
    FILE *f = fopen(file_name, "w");

    fprintf(f, "%d\n", winner);
    if(winner != None)
        fprintf(f, "%d %d\n", sc.player1, sc.player2);
    fprintf(f, "%d %d\n", p1.type_of_player, p2.type_of_player);
    fprintf(f, "%s\n", p1.player_name);
    fprintf(f, "%s\n", p2.player_name);
    fprintf(f, "%c %c", p.player1, p.player2);

    fclose(f);
}

void playGame(int row_g, int col_g, int player1_type, int player2_type, int game_id)
{
    char his_move;
    int someone_win = None, player_turn, stop, total_coup = 0;
    Element* game_stack = NULL;
    Score sc;

    if(game_id == 0)
    {
        initializeScores(&sc, row_g, col_g);
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
        /*loadScores(&sc, row_g, col_g, game_id);
        grid = loadGrid(row_g, col_g, game_id);
        game_stack = pushElement(game_stack, grid);
        loadPlayersHuman(&p1, Player1);
        if(player2_type == Human)
            loadPlayersHuman(&p2, Player2);
        else
            loadPlayersAI(&p2, Player2);
        player_turn = Player1;*/
    }

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
                        player_turn = Player2;
                    else
                        player_turn = Player1;
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
    game_stack = saveGamePlay(p1, p2, game_stack, row_g, col_g, game_id, someone_win, sc);

    grid = deleteGrid(grid, row_g);
}