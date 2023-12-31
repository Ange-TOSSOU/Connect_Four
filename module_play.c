#include "module_play.h"

void initializePlayersHuman(Player* p, int num)
{
    char tmp[ROW_TEXT+2] = "", nump[3] = "";
    int n;
    TypePieces pt = getDefaultTypePieces();
    ColorPieces pc = getDefaultColorPieces();

    do{
        strcpy(tmp, "Player ");
        itoa((num+3)/2, nump, 10);
        strcat(tmp, nump);
        strcat(tmp, ", give your name : ");
        printOnNChar(tmp, ROW_TEXT, 0);
        fgets(p->player_name, ROW_TEXT+2, stdin);
        n = strlen(p->player_name);
        if(p->player_name[n-1] == '\n')
            p->player_name[n-1] = 0;
        else
            while(getchar() != '\n');
    }while(strlen(p->player_name)<1);

    if(num == Player1)
    {
        strcpy(p->color_of_piece, pc.player1);
        p->type_of_piece = pt.player1;
    }
    else if(num == Player2)
    {
        strcpy(p->color_of_piece, pc.player2);
        p->type_of_piece = pt.player2;
    }

    p->type_of_player = Human;
    p->score = (ROW_GRID*COL_GRID)/2 + 4;
    p->time = 0;
    p->is_winner = -1;
}

void initializePlayersAI(Player* p, int num)
{
    char tmp[ROW_TEXT+2] = "", nump[3] = "";
    TypePieces pt = getDefaultTypePieces();
    ColorPieces pc = getDefaultColorPieces();
    
    strcpy(tmp, "Player ");
    itoa((num+3)/2, nump, 10);
    strcat(tmp, nump);
    strcat(tmp, " is AI.");
    printOnNChar(tmp, ROW_TEXT, 0);
    printf("\n");

    strcpy(p->player_name, "AI");

    if(num == Player1)
    {
        strcpy(p->color_of_piece, pc.player1);
        p->type_of_piece = pt.player1;
    }
    else if(num == Player2)
    {
        strcpy(p->color_of_piece, pc.player2);
        p->type_of_piece = pt.player2;
    }

    p->type_of_player = AI;
    p->score = (ROW_GRID*COL_GRID)/2 + 4;
    p->time = 0;
    p->is_winner = -1;
}

DWORD WINAPI thread_for_choice(void* pVar)
{
    *(char*)pVar = getchar();

    if(*(char*)pVar != '\n')
        while(getchar() != '\n');

    return 0;
}

char getMove(Player p)
{
    char c = 0, tmp[ROW_TEXT+1] = "", num[3] = "";
    int i = 0;
    HANDLE thread;
    
    while(!( ('1'<=c && c<='7') || c=='u' || c=='q'))
    {
        c = 0;
        thread = CreateThread(NULL, 0, thread_for_choice, &c, 0, NULL);

        while(c == 0 && i < 200)
        {
            if(i%50 == 0)
            {
                strcpy(tmp, p.player_name);
                strcat(tmp, ", make a move (");
                itoa(20-i/10, num, 10);
                strcat(tmp, num);
                strcat(tmp, " s remaining) : ");
                printf("\n");
                printOnNChar(tmp, ROW_TEXT, 0);
            }
            Sleep(100);
            ++i;
        }

        if(i == 200)
        {
            printf("\n");
            printOnNChar("Time out, press any key to continue : ", ROW_TEXT, 0);
            WaitForSingleObject(thread, INFINITE);
            c = '0' + (rand()%(7)+1);
        }
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
    FILE *f = fopen(file_name, "a+");

    fprintf(f, "%d\n", winner);
    fprintf(f, "%d %d\n", p1.score, p2.score);
    fprintf(f, "%ld %ld\n", p1.time, p2.time);
    fprintf(f, "%d\n", player_turn);
    fprintf(f, "%d %d\n", p1.type_of_player, p2.type_of_player);
    fprintf(f, "%s\n", p1.player_name);
    fprintf(f, "%s\n", p2.player_name);
    fprintf(f, "%c %c\n", p1.type_of_piece, p2.type_of_piece);
    fprintf(f, "%s %s", p1.color_of_piece, p2.color_of_piece);

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
    printf("\n\n");

    c = 0;
    while(!(1<=c && c<=j+1))
        c = get_choice();
    
    if(c < j+1) /* If the player want to play a game */
        c = tab[c-1];
    else /* If c==j+1 ie the player want to exit */
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
    time_t t_begin, t_end;
    Player p1, p2;
    Element* game_stack = NULL;

    initializeDefaultSettings();

    grid = initializeGrid();

    game_id = getGameIdNotFinish();
    if(game_id == -1) /* To exit */
        return;
    else if(game_id == 0) /* For a new game */
    {
        system("cls");
        game_stack = pushElement(game_stack, grid);
        initializePlayersHuman(&p1, Player1);
        if(player2_type == Human)
            initializePlayersHuman(&p2, Player2);
        else
            initializePlayersAI(&p2, Player2);
        player_turn = Player1;
    }
    else /* To continue an old game */
    {
        game_stack = loadGameStack(game_id);
        loadGrid(game_stack, grid);
        player_turn = loadPlayers(&p1, &p2, game_id);
    }

    someone_win = None;
    while(!someone_win)
    {
        system("cls");
        printGrid(grid, p1, p2);
        printf("\n");
        
        stop = 0;
        t_begin = time(NULL);
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
                    t_end = time(NULL);
                    total_coup -= 2;
                    ++p1.score;
                    ++p2.score;
                    stop = 1;
                    if(player_turn == Player1)
                        p1.time += (t_end-t_begin);
                    else
                        p2.time += (t_end-t_begin);
                }
                else
                    stop = 0;
            }
            else if(his_move == 'q')
            {
                t_end = time(NULL);
                someone_win = QuitGame;
                stop = 1;
                if(player_turn == Player1)
                    p1.time += (t_end-t_begin);
                else
                    p2.time += (t_end-t_begin);
            }
            else if('1'<=his_move && his_move<='7')
            {
                t_end = time(NULL);
                stop = move(grid, player_turn, his_move-'0' -1);

                if(stop)
                {
                    ++total_coup;
                    game_stack = pushElement(game_stack, grid);

                    if(player_turn == Player1)
                    {
                        --p1.score;
                        p1.time += (t_end-t_begin);
                        player_turn = Player2;
                    }
                    else
                    {
                        --p2.score;
                        p2.time += (t_end-t_begin);
                        player_turn = Player1;
                    }
                }
            }
            else
                exit(EXIT_FAILURE);
        }

        if(someone_win!=QuitGame && '1'<=his_move && his_move<='7')
            someone_win = whoWin(grid, his_move-'0'-1, total_coup);
        
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
