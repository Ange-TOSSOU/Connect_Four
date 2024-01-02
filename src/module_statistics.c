#include "../include/module_statistics.h"

void printStatistics()
{
    char file_name_g[ROW_TEXT+1] = "", num[3] = "";
    int lim = getNumberOfGamesSaved(), i;
    Player p1, p2;
    Elementp *lp = NULL;
    Elementn *ln = NULL, *tmpln;

    for(i = 1; i <= lim; ++i)
    {
        strcpy(file_name_g, FILE_NAME_SAVE_PLAY);
        itoa(i, num, 10);
        strcat(file_name_g, num);
        strcat(file_name_g, ".txt");

        if(exist(file_name_g))
        {
            loadPlayers(&p1, &p2, i);
            lp = pushElement_Player(lp, p1);
            ln = pushElement_Name(ln, p1.player_name);
            lp = pushElement_Player(lp, p2);
            ln = pushElement_Name(ln, p2.player_name);
        }
    }

    tmpln = ln;
    while(tmpln != NULL)
    {
        printStatisticsForPlayer(lp, tmpln->name);
        tmpln = tmpln->next;
    }

    if(lim < 1)
        printOnNChar("NO GAME FOUND !", ROW_TEXT, 0);
    
    printf("\n\n");
    printOnNChar("Press enter key to go back to the menu : ", ROW_TEXT, 0);
    while(getchar() != '\n');

    lp = cleanStack_Player(lp);
    ln = cleanList_Name(ln);
}

void printStatisticsForPlayer(Elementp *lp, char *name)
{
    char num[3] = "", message[ROW_TEXT+1] = "";
    int start = 1, i = 1, n_won = 0, n_lost = 0, n_draw = 0, n_still = 0;
    Elementp *tmplp = lp;

    while(tmplp != NULL)
    {
        if(strcmp(tmplp->p.player_name, name) == 0)
        {
            if(start)
            {
                printOnNChar(name, ROW_TEXT, 0);
                printf("\n");
                printOnNChar("", ROW_TEXT, 0);
                printf("+--------+---------------------+---------+----------------+\n");
                printOnNChar("", ROW_TEXT, 0);
                printf("|  Game  |     Time (in s)     |  Score  |     Status     |\n");
                printOnNChar("", ROW_TEXT, 0);
                printf("+--------+---------------------+---------+----------------+\n");
                start = 0;
            }
            printOnNChar("", ROW_TEXT, 0);
            if(tmplp->p.is_winner == 1)
            {
                printf("|  %4d  |  %17ld  |  %5d  |       \033[92mWon\033[0m      |\n", i, tmplp->p.time, tmplp->p.score);
                ++n_won;
            }
            else if(tmplp->p.is_winner == 0)
            {
                printf("|  %4d  |  %17ld  |    -    |      \033[91mLost\033[0m      |\n", i, tmplp->p.time);
                ++n_lost;
            }
            else if(tmplp->p.is_winner == Both)
            {
                printf("|  %4d  |  %17ld  |  %5d  |      \033[95mDraw\033[0m      |\n", i, tmplp->p.time, tmplp->p.score);
                ++n_draw;
            }
            else
            {
                printf("|  %4d  |          -          |    -    |  Not Finished  |\n", i);
                ++n_still;
            }
            printOnNChar("", ROW_TEXT, 0);
            printf("+--------+---------------------+---------+----------------+\n");
            ++i;
        }

        tmplp = tmplp->next;
    }

    if(start == 0)
    {
        strcpy(message, "Number of game(s) won : ");
        itoa(n_won, num, 10);
        strcat(message, num);
        printOnNChar(message, ROW_TEXT, 0);
        printf("\n");
        strcpy(message, "Number of game(s) lost : ");
        itoa(n_lost, num, 10);
        strcat(message, num);
        printOnNChar(message, ROW_TEXT, 0);
        printf("\n");
        strcpy(message, "Number of game(s) draw : ");
        itoa(n_draw, num, 10);
        strcat(message, num);
        printOnNChar(message, ROW_TEXT, 0);
        printf("\n");
        strcpy(message, "Number of game(s) not finished : ");
        itoa(n_still, num, 10);
        strcat(message, num);
        printOnNChar(message, ROW_TEXT, 0);
    }
    printf("\n\n");
}