#ifndef SHAREDH
#define SHAREDH

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define ROW_GRID 6
#define COL_GRID 7
#define ROW_TEXT 80
#define N 30
#define N_CONFS 100
#define LIMIT_TIME 20
#define FILE_NAMED "default_settings.txt"
#define FILE_NAMEP "possible_type_pieces.txt"
#define FILE_NAMEC "possible_color_pieces.txt"
#define FILE_NAMEL "possible_level.txt"
#define FILE_NAME_NUMBER_OF_GAMES_SAVED "number_of_games_saved.txt"
#define FILE_NAME_SAVE_PLAY "old_game_play_"
#define FILE_NAME_SAVE_SETTINGS "old_game_settings_"

enum TPlayer {Player1=-1, None, Player2, Both, QuitGame};
enum Player_Type {Human=1, AI};

typedef struct
{
    char player_name[ROW_TEXT+1];
    char color_of_piece[N_CONFS+1];
    char type_of_piece;
    int type_of_player;
    int score;
    time_t time;
    int is_winner;
}Player;

int get_choice();
void printNChar(char, int);
void printOnNChar(char*, int, int);
int game_not_finish(char*);
int loadPlayers(Player*, Player*, int);
int getNumberOfGamesSaved();

#endif