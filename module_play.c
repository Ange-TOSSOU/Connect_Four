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

Element* saveGamePlay(Element* game_stack, int row_g, int col_g)
{
    int **tmp = initializeGrid(row_g, col_g);
    Element *reverse_stack = NULL;
    FILE *f = NULL;

    while(game_stack != NULL)
    {
        game_stack = popElement(game_stack, tmp);
        reverse_stack = pushElement(reverse_stack, tmp);
    }
    
    f = fopen(FILE_NAMESP, "r");
    if(f != NULL)
    {
        fclose(f);
        remove(FILE_NAMESP);
    }

    while(reverse_stack != NULL)
    {
        reverse_stack = popElement(reverse_stack, tmp);
        if(reverse_stack == NULL)
            addLine(FILE_NAMESP, tmp, row_g, col_g, '\0');
        else
            addLine(FILE_NAMESP, tmp, row_g, col_g, '\n');
    }

    tmp = deleteGrid(tmp, row_g);

    return NULL;
}

void saveGameSettings(Player p1, Player p2)
{
    /*char tmp[]
    FILE *f = NULL;
    
    f = fopen(FILE_NAMESS, "r");
    if(f != NULL)
    {
        fclose(f);
        remove(FILE_NAMESP);
    }

    f = fopen(FILE_NAMESS, "a+");*/
}

void playGame(int row_g, int col_g, int player1_type, int player2_type)
{
    char his_move;
    int someone_win = 0, player_turn, stop;
    Element* game_stack = NULL;

    grid = initializeGrid(row_g, col_g);
    game_stack = pushElement(game_stack, grid);

    initializePlayersHuman(&p1, Player1);
    if(player2_type == Human)
        initializePlayersHuman(&p2, Player2);
    else
        initializePlayersAI(&p2, Player2);
    
    player_turn = Player1;
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
                    stop = 1;
                else
                    stop = 0;
            }
            else if(his_move == 'q')
            {
                stop = 1;
                someone_win = 2;
            }
            else if('1'<=his_move && his_move<='7')
            {
                stop = move(grid, player_turn, his_move-'0' -1, ROW_GRID);

                if(stop)
                {
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

        if('1'<=his_move && his_move<='7')
            someone_win = whoWin(grid, his_move-'0' -1, row_g, col_g);
    }

    saveGameSettings(p1, p2);
    game_stack = saveGamePlay(game_stack, row_g, col_g);

    grid = deleteGrid(grid, row_g);
}