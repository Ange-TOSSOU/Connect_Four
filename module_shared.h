#ifndef SHAREDH
#define SHAREDH

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ROW_GRID 6
#define COL_GRID 7
#define ROW_TEXT 80
#define N 30
#define FILE_NAMED "default_settings.txt"
#define FILE_NAMEP "possible_type_pieces.txt"
#define FILE_NAMEL "possible_level.txt"
#define FILE_NAME_NUMBER_OF_GAMES_SAVED "number_of_games_saved.txt"
#define FILE_NAME_SAVE_PLAY "old_game_play_"
#define FILE_NAME_SAVE_SETTINGS "old_game_settings_"

enum TPlayer {Player1=-1, None, Player2, Both, QuitGame};
enum Player_Type {Human=1, AI};

typedef struct
{
    char player_name[N+1];
    char type_of_piece;
    int type_of_player;
    int score;
}Player;

void printNChar(char, int);
void printOnNChar(char*, int, int);
int game_not_finish(char*);
int loadPlayers(Player*, Player*, int);
int getNumberOfGamesSaved();

#endif