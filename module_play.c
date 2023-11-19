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

void play_game(int row_g, int col_g, int player1_type, int player2_type)
{
    char his_move;
    int someone_win = 0, player_turn, stop;

    grid = initializeGrid(row_g, col_g);

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
                printf("Go back one step.\n");
            }
            else if(his_move == 'q')
            {
                printf("Quit.\n");
            }
            else if('1'<=his_move && his_move<='7')
                stop = move(grid, player_turn, his_move-'0' -1, ROW_GRID);
            else
                stop = 0;
        }

        if(player_turn == Player1)
            player_turn = Player2;
        else
            player_turn = Player1;

        someone_win = whoWin(grid, his_move-'0' -1, ROW_GRID, COL_GRID);
    }

    grid = deleteGrid(grid, row_g);
}