#include "module_settings.h"

void initializeDefaultSettings()
{
    FILE *f = fopen(FILE_NAME, "r");

    if(f == NULL)
    {
        f = fopen(FILE_NAME, "a");
        if(f == NULL)
        {
            printf("Unable to create the conf_settings file.\n");
            exit(EXIT_FAILURE);
        }
        fprintf(f, "TypeP_1 x o\n");
        fprintf(f, "TypeP_2 + o\n");
        fprintf(f, "DefaultTypeP x o\n");
        fprintf(f, "LevelAI_1 1\n");
        fprintf(f, "LevelAI_2 2\n");
        fprintf(f, "LevelAI_3 3\n");
        fprintf(f, "DefaultLevelAI 1");
        fclose(f);
    }
}

TypePieces getDefaultTypePieces()
{
    char tmp[N_CONFS+1], *origin;
    FILE *f = fopen(FILE_NAME, "r");
    TypePieces p;

    fseek(f, 0, SEEK_SET);
    while(fgets(tmp, N_CONFS+1, f))
    {
        if(strstr(tmp, "DefaultTypeP"))
        {
            //printf("%s", tmp);
            origin = strrchr(tmp, ' ');
            //printf("%s", origin);
            p.player1 = origin[1];
            p.player2 = origin[3];
            break;
        }
    }

    return p;
}

int getDefaultAILevel()
{
    char tmp[N_CONFS+1], *origin;
    int level;
    FILE *f = fopen(FILE_NAME, "r");

    fseek(f, 0, SEEK_SET);
    while(fgets(tmp, N_CONFS+1, f))
    {
        if(strstr(tmp, "DefaultAILevel"))
        {
            //printf("%s", tmp);
            origin = strrchr(tmp, ' ');
            //printf("%s", origin);
            level = atoi(origin);
            break;
        }
    }

    return level;
}

void printDefaultSettings()
{
    char player[ROW_TEXT+1];
    int level = getDefaultAILevel(), tmp;
    TypePieces p = getDefaultTypePieces();

    printOnNChar("SETTINGS", ROW_TEXT, 0);
    printf("\n");

    if(level == Beginner)
        printOnNChar("- AI Level : Beginner", ROW_TEXT, 4);
    else if(level == Intermediate)
        printOnNChar("- AI Level : Intermediate", ROW_TEXT, 4);
    else
        printOnNChar("- AI Level : Advanced", ROW_TEXT, 4);
    printf("\n");

    strcpy(player, "- Type of piece (player 1) : ");
    tmp = strlen(player);
    player[tmp] = p.player1;
    player[tmp+1] = 0;
    printOnNChar(player, ROW_TEXT, 4);
    printf("\n");
    strcpy(player, "- Type of piece (player 2) : ");
    tmp = strlen(player);
    player[tmp] = p.player2;
    player[tmp+1] = 0;
    printOnNChar(player, ROW_TEXT, 4);
}

void settings()
{
    initializeDefaultSettings();
    printDefaultSettings();
}