#include "module_settings.h"

void initializeDefaultSettings()
{
    FILE *f = fopen(FILE_NAMED, "r");

    if(f == NULL)
    {
        f = fopen(FILE_NAMED, "a");
        if(f == NULL)
        {
            printf("Unable to create the default_settings file.\n");
            exit(EXIT_FAILURE);
        }
        fprintf(f, "x o\n");
        fprintf(f, "1");
        fclose(f);
    }
    else
        fclose(f);
}

// yellow(93), blue(94), white(97), magenta(95), red(91), green(92), cyan(96)

void initializePiecesSettings()
{
    FILE *f = fopen(FILE_NAMEP, "r");

    if(f == NULL)
    {
        f = fopen(FILE_NAMEP, "a");
        if(f == NULL)
        {
            printf("Unable to create the default_settings file.\n");
            exit(EXIT_FAILURE);
        }
        fprintf(f, "x o\n");
        fprintf(f, "x +\n");
        fprintf(f, "o +");
        fclose(f);
    }
    else
        fclose(f);
}

void initializeLevelSettings()
{
    FILE *f = fopen(FILE_NAMEL, "r");

    if(f == NULL)
    {
        f = fopen(FILE_NAMEL, "a");
        if(f == NULL)
        {
            printf("Unable to create the default_settings file.\n");
            exit(EXIT_FAILURE);
        }
        fprintf(f, "1\n");
        fprintf(f, "2\n");
        fprintf(f, "3");
        fclose(f);
    }
    else
        fclose(f);
}

TypePieces getDefaultTypePieces()
{
    char tmp[N_CONFS+1];
    int i;
    FILE *f = fopen(FILE_NAMED, "r");
    TypePieces p = {'x', 'o'};

    fseek(f, 0, SEEK_SET);
    for(i = 0; i < 1; ++i)
        fgets(tmp, N_CONFS+1, f);

    p.player1 = tmp[0];
    p.player2 = tmp[2];

    fclose(f);

    return p;
}

int getDefaultAILevel()
{
    char tmp[N_CONFS+1];
    int level = Beginner, i;
    FILE *f = fopen(FILE_NAMED, "r");

    fseek(f, 0, SEEK_SET);
    for(i = 0; i < 2; ++i)
        fgets(tmp, N_CONFS+1, f);

    level = atoi(tmp);

    fclose(f);

    return level;
}

void printDefaultSettings()
{
    char player[ROW_TEXT+1];
    int level = getDefaultAILevel(), tmp;
    TypePieces p = getDefaultTypePieces();

    printOnNChar("DEFAULT SETTINGS", ROW_TEXT, 0);
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

void setDefaultTypePieces(TypePieces p)
{
    char tmp[4+1] = "";

    tmp[0] = p.player1;
    tmp[1] = ' ';
    tmp[2] = p.player2;
    tmp[3] = '\n';

    changeLine(FILE_NAMED, LINE_D_P, tmp);
}

void setDefaultAILevel(int level)
{
    char tmp[2+1] = "";
    
    tmp[0] = '0'+level;
    tmp[1] = '\n';

    changeLine(FILE_NAMED, LINE_D_L, tmp);
}

int get_change_choice()
{
    int c;
    printOnNChar("Make a choice : ", ROW_TEXT, 0);
    scanf("%d", &c);
    while(getchar() != '\n');

    return c;
}

void settings()
{
    char tmp[N_CONFS+1], to_print[N_CONFS+1], tmpp[N_CONFS+1];
    int c = 'y', want_to_change, choice, i, j;
    TypePieces p;
    FILE *f = NULL;
    initializeDefaultSettings();
    initializePiecesSettings();
    initializeLevelSettings();
    while(c == 'y')
    {
        system("cls");
        printDefaultSettings();
        printf("\n");
        printOnNChar("Do you want to change a setting (y/n) : ", ROW_TEXT, 0);
        c = getchar();
        if(c != '\n')
            while(getchar() != '\n');
        if(c == 'y')
        {
            printf("\n");
            printOnNChar("Change the AI level", ROW_TEXT, 0);
            printf("\n");
            printOnNChar("1- Change to beginner", ROW_TEXT, 4);
            printf("\n");
            printOnNChar("2- Change to intermediate", ROW_TEXT, 4);
            printf("\n");
            printOnNChar("3- Change to advanced", ROW_TEXT, 4);
            printf("\n");
            printOnNChar("Change the type of pieces", ROW_TEXT, 0);
            printf("\n");
            f = fopen(FILE_NAMEP, "r");
            fseek(f, 0, SEEK_SET);
            for(i = 4; fgets(tmp, N_CONFS+1, f); ++i)
            {
                for(j = 0; tmp[j]; ++j)
                {
                    if(tmp[j] == '\n')
                    {
                        tmp[j] = '\0';
                        break;
                    }
                }
                tmp[j] = '\0';
                tmpp[0] = to_print[0] = '\0';
                itoa(i, tmpp, 10);
                strcat(to_print, tmpp);
                strcat(to_print, "- Change to {");
                strcat(to_print, tmp);
                strcat(to_print, "}");
                printOnNChar(to_print, ROW_TEXT, 4);
                printf("\n");
            }
            fclose(f);
            printf("\n");
            want_to_change = 1;
            while(want_to_change)
            {
                choice = get_change_choice();
                if(choice == Beginner || choice == Intermediate || choice == Advanced)
                {
                    setDefaultAILevel(choice);
                    want_to_change = 0;
                }
                else if(4 <= choice && choice < i)
                {
                    f = fopen(FILE_NAMEP, "r");
                    fseek(f, 0, SEEK_SET);
                    for(j = 0; (j < choice-3) && (fgets(tmp, N_CONFS+1, f)); ++j);
                    fclose(f);
                    p.player1 = tmp[0];
                    p.player2 = tmp[2];
                    setDefaultTypePieces(p);
                    want_to_change = 0;
                }
                else
                    want_to_change = 1;
            }
        }
    }
}