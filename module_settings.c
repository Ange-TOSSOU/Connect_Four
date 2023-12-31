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
        fprintf(f, "1\n");
        fprintf(f, "yellow blue");
        fclose(f);
    }
    else
        fclose(f);
}

// yellow(93), blue(94), white(97), magenta(95), cyan(96)

void initializePiecesTSettings()
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

void initializePiecesCSettings()
{
    FILE *f = fopen(FILE_NAMEC, "r");

    if(f == NULL)
    {
        f = fopen(FILE_NAMEC, "a");
        if(f == NULL)
        {
            printf("Unable to create the default_settings file.\n");
            exit(EXIT_FAILURE);
        }
        fprintf(f, "yellow blue\n");
        fprintf(f, "yellow white\n");
        fprintf(f, "yellow magenta\n");
        fprintf(f, "yellow cyan");
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

ColorPieces getDefaultColorPieces()
{
    char tmp[N_CONFS+1];
    int i;
    FILE *f = fopen(FILE_NAMED, "r");
    ColorPieces p = {"yellow", "blue"};

    fseek(f, 0, SEEK_SET);
    for(i = 0; i < 2; ++i)
        fgets(tmp, N_CONFS+1, f);

    fscanf(f, "%s", p.player1);
    fscanf(f, "%s", p.player2);

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
    char message[ROW_TEXT+1];
    int level = getDefaultAILevel();
    TypePieces pt = getDefaultTypePieces();
    ColorPieces pc = getDefaultColorPieces();

    printOnNChar("DEFAULT SETTINGS", ROW_TEXT, 0);
    printf("\n");

    if(level == Beginner)
        printOnNChar("- AI Level : Beginner", ROW_TEXT, 4);
    else if(level == Intermediate)
        printOnNChar("- AI Level : Intermediate", ROW_TEXT, 4);
    else
        printOnNChar("- AI Level : Advanced", ROW_TEXT, 4);
    printf("\n");

    strcpy(message, "- Piece (player 1) : ");
    printOnNChar(message, ROW_TEXT, 4);
    if(strcmp(pc.player1, "yellow") == 0)
        printf("\033[93m%c\033[0m", pt.player1);
    else if(strcmp(pc.player1, "blue") == 0)
        printf("\033[94m%c\033[0m", pt.player1);
    else if(strcmp(pc.player1, "magenta") == 0)
        printf("\033[95m%c\033[0m", pt.player1);
    else if(strcmp(pc.player1, "cyan") == 0)
        printf("\033[96m%c\033[0m", pt.player1);
    else if(strcmp(pc.player1, "white") == 0)
        printf("\033[97m%c\033[0m", pt.player1);
    else
        printf("%c", pt.player1);
    printf("\n");
    strcpy(message, "- Piece (player 2) : ");
    printOnNChar(message, ROW_TEXT, 4);
    if(strcmp(pc.player2, "yellow") == 0)
        printf("\033[93m%c\033[0m", pt.player2);
    else if(strcmp(pc.player2, "blue") == 0)
        printf("\033[94m%c\033[0m", pt.player2);
    else if(strcmp(pc.player2, "magenta") == 0)
        printf("\033[95m%c\033[0m", pt.player2);
    else if(strcmp(pc.player2, "cyan") == 0)
        printf("\033[96m%c\033[0m", pt.player2);
    else if(strcmp(pc.player2, "white") == 0)
        printf("\033[97m%c\033[0m", pt.player2);
    else
        printf("%c", pt.player2);
    printf("\n");
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

void setDefaultColorPieces(ColorPieces p)
{
    char tmp[N_CONFS] = "";

    strcpy(tmp, p.player1);
    strcat(tmp, " ");
    strcat(tmp, p.player2);

    changeLine(FILE_NAMED, LINE_D_C, tmp);
}

void setDefaultAILevel(int level)
{
    char tmp[2+1] = "";
    
    tmp[0] = '0'+level;
    tmp[1] = '\n';

    changeLine(FILE_NAMED, LINE_D_L, tmp);
}

void changeLevelSettings()
{
    char message[N_CONFS+1], num[3] = "";
    int want_to_change, choice, i, j, lev[3] = {0}, current_level = getDefaultAILevel();

    system("cls");

    if(current_level == Beginner)
        printOnNChar("Current AI Level : Beginner", ROW_TEXT, 0);
    else if(current_level == Intermediate)
        printOnNChar("Current AI Level : Intermediate", ROW_TEXT, 0);
    else
        printOnNChar("Current AI Level : Advanced", ROW_TEXT, 0);
    printf("\n\n");

    printOnNChar("Change the AI level", ROW_TEXT, 0);
    printf("\n");
    for(i = 0, j=0; i<3; ++i)
    {
        if(current_level != i+1)
        {
            ++j;
            itoa(j, num, 10);
            strcpy(message, num);
            if(i+1 == Beginner)
                strcat(message, "- To beginner");
            else if(i+1 == Intermediate)
                strcat(message, "- To intermediate");
            else
                strcat(message, "- To advanced");
            lev[i] = 1;
            printOnNChar(message, ROW_TEXT, 4);
            printf("\n");
        }
        else
            lev[i] = 0;
    }
    itoa(j+1, num, 10);
    strcpy(message, num);
    strcat(message, "- Exit");
    printOnNChar(message, ROW_TEXT, 4);
    printf("\n\n");

    want_to_change = 1;
    while(want_to_change)
    {
        choice = get_choice();
        if(1<=choice && choice<=j)
        {
            for(i=0, j=0; i<3 && j!=choice; ++i)
            {
                if(lev[i])
                    ++j;
            }
            setDefaultAILevel(i);
            want_to_change = 0;
        }
        else if(choice == j+1)
            want_to_change = 0;
        else
            want_to_change = 1;
    }
}

void changeTpieceSettings()
{
    char message[N_CONFS+1], num[3] = "";
    int want_to_change, choice, i, j, tmp, n;
    TypePieces *type = NULL, current_pt = getDefaultTypePieces();
    FILE *f = NULL;

    system("cls");

    f = fopen(FILE_NAMEP, "r");
    fseek(f, 0, SEEK_SET);
    for(n = 0; fgets(message, N_CONFS+1, f); ++n);
    type = (TypePieces*)malloc(n*sizeof(TypePieces));

    fseek(f, 0, SEEK_SET);
    for(i = 0; fgets(message, N_CONFS+1, f); ++i)
    {
        type[i].player1 = message[0];
        type[i].player2 = message[2];
    }
    fclose(f);

    for(i = 0; i<n; ++i)
    {
        if(current_pt.player1==type[i].player1 && current_pt.player2==type[i].player2)
        {
            strcpy(message, "Current type of pieces : {");
            tmp = strlen(message);
            message[tmp] = type[i].player1;
            message[tmp+1] = '\0';
            strcat(message, ", ");
            tmp = strlen(message);
            message[tmp] = type[i].player2;
            message[tmp+1] = '\0';
            strcat(message, "}");
            printOnNChar(message, ROW_TEXT, 0);
            printf("\n\n");
            break;
        }
    }

    printOnNChar("Change the type of pieces", ROW_TEXT, 0);
    printf("\n");
    for(i = 0, j=0; i<n; ++i)
    {
        if(current_pt.player1!=type[i].player1 || current_pt.player2!=type[i].player2)
        {
            ++j;
            itoa(j, num, 10);
            strcpy(message, num);
            strcat(message, "- To {");
            tmp = strlen(message);
            message[tmp] = type[i].player1;
            message[tmp+1] = '\0';
            strcat(message, ", ");
            tmp = strlen(message);
            message[tmp] = type[i].player2;
            message[tmp+1] = '\0';
            strcat(message, "}");
            printOnNChar(message, ROW_TEXT, 4);
            printf("\n");
        }
        else
            type[i].player1 = type[i].player2 = 0;
    }
    itoa(j+1, num, 10);
    strcpy(message, num);
    strcat(message, "- Exit");
    printOnNChar(message, ROW_TEXT, 4);
    printf("\n\n");

    want_to_change = 1;
    while(want_to_change)
    {
        choice = get_choice();
        if(1<=choice && choice<=j)
        {
            for(i=0, j=0; i<3 && j!=choice; ++i)
            {
                if(type[i].player1 && type[i].player2)
                    ++j;
            }
            setDefaultTypePieces(type[i-1]);
            want_to_change = 0;
        }
        else if(choice == j+1)
            want_to_change = 0;
        else
            want_to_change = 1;
    }
}

void printColor(char *name)
{
    if(strcmp(name, "yellow") == 0)
        printf("\033[93myellow\033[0m");
    else if(strcmp(name, "blue") == 0)
        printf("\033[94mblue\033[0m");
    else if(strcmp(name, "magenta") == 0)
        printf("\033[95mmagenta\033[0m");
    else if(strcmp(name, "cyan") == 0)
        printf("\033[96mcyan\033[0m");
    else
        printf("\033[97mwhite\033[0m");
}

void changeCpieceSettings()
{
    char message[N_CONFS+1], num[3] = "", *token;
    int want_to_change, choice, i, j, n;
    ColorPieces *color = NULL, current_pc = getDefaultColorPieces();
    FILE *f = NULL;

    system("cls");

    f = fopen(FILE_NAMEC, "r");
    fseek(f, 0, SEEK_SET);
    for(n = 0; fgets(message, N_CONFS+1, f); ++n);
    color = (ColorPieces*)malloc(n*sizeof(ColorPieces));

    fseek(f, 0, SEEK_SET);
    for(i = 0; fgets(message, N_CONFS+1, f); ++i)
    {
        if(message[strlen(message)-1] == '\n')
            message[strlen(message)-1] = '\0';
        token = strtok(message, " ");
        for(j=1; token != NULL; ++j)
        {
            if(j == 1)
                strcpy(color[i].player1, token);
            else if(j == 2)
                strcpy(color[i].player2, token);
    
            token = strtok(NULL, " ");
        }
    }
    fclose(f);

    printOnNChar("Current color of pieces : {", ROW_TEXT, 0);
    printColor(current_pc.player1);
    printf(", ");
    printColor(current_pc.player2);
    printf("}");
    printf("\n\n");

    printOnNChar("Change the color of pieces", ROW_TEXT, 0);
    printf("\n");
    for(i = 0, j=0; i<n; ++i)
    {
        if(strcmp(current_pc.player1,color[i].player1)!=0 || strcmp(current_pc.player2,color[i].player2)!=0)
        {
            ++j;
            itoa(j, num, 10);
            strcpy(message, num);
            strcat(message, "- To {");
            printOnNChar(message, ROW_TEXT, 4);
            printColor(color[i].player1);
            printf(", ");
            printColor(color[i].player2);
            printf("}");
            printf("\n");
        }
        else
        {
            strcpy(color[i].player1, "");
            strcpy(color[i].player2, "");
        }
    }
    itoa(j+1, num, 10);
    strcpy(message, num);
    strcat(message, "- Exit");
    printOnNChar(message, ROW_TEXT, 4);
    printf("\n\n");

    want_to_change = 1;
    while(want_to_change)
    {
        choice = get_choice();
        if(1<=choice && choice<=j)
        {
            for(i=0, j=0; i<3 && j!=choice; ++i)
            {
                if(strlen(color[i].player1)!=0 && strlen(color[i].player2)!=0)
                    ++j;
            }
            setDefaultColorPieces(color[i-1]);
            want_to_change = 0;
        }
        else if(choice == j+1)
            want_to_change = 0;
        else
            want_to_change = 1;
    }
}

void settings()
{
    int c = 'y', want_to_change, choice;

    initializeDefaultSettings();
    initializePiecesTSettings();
    initializePiecesCSettings();
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
            system("cls");
            printOnNChar("1- Change the AI level", ROW_TEXT, 0);
            printf("\n");
            printOnNChar("2- Change the type of piece", ROW_TEXT, 0);
            printf("\n");
            printOnNChar("3- Change the color of piece", ROW_TEXT, 0);
            printf("\n");
            printOnNChar("4- Exit", ROW_TEXT, 0);
            printf("\n\n");
            want_to_change = 1;
            while(want_to_change)
            {
                choice = get_choice();
                if(choice == 1)
                {
                    changeLevelSettings();
                    want_to_change = 0;
                }
                else if(choice == 2)
                {
                    changeTpieceSettings();
                    want_to_change = 0;
                }
                else if(choice == 3)
                {
                    changeCpieceSettings();
                    want_to_change = 0;
                }
                else if(choice == 4)
                    want_to_change = 0;
                else
                    want_to_change = 1;
            }
        }
    }
}
