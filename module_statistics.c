#include "module_statistics.h"

void initializeScores(Score* sc, int row_g, int col_g)
{
    sc->player1 = sc->player2 = (row_g*col_g)/2 + 4;
}

void updateScores(Score* sc, int player_turn, int winner)
{
    /*if(player_turn == Player1)
    {
        if(winner != player_turn)
            --(sc->player1);
    }
    else if(player_turn == Player2)
    {
        if(winner != player_turn)
            --(sc->player2);
    }*/
}