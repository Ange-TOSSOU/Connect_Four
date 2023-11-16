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
        fprintf(f, "DefaultTypeP x o\n");
        fprintf(f, "DefaultAILevel 1");
        fclose(f);
    }
    else
        fclose(f);
}

TypePieces getDefaultTypePieces()
{
    char tmp[N_CONFS+1], *origin;
    FILE *f = fopen(FILE_NAME, "r");
    TypePieces p = {'x', 'o'};

    fseek(f, 0, SEEK_SET);
    while(fgets(tmp, N_CONFS+1, f))
    {
        if(strstr(tmp, "DefaultTypeP"))
        {
            origin = strchr(tmp, ' ');
            p.player1 = origin[1];
            p.player2 = origin[3];
            break;
        }
    }

    fclose(f);

    return p;
}

int getDefaultAILevel()
{
    char tmp[N_CONFS+1], *origin;
    int level = Beginner;
    FILE *f = fopen(FILE_NAME, "r");

    fseek(f, 0, SEEK_SET);
    while(fgets(tmp, N_CONFS+1, f))
    {
        if(strstr(tmp, "DefaultAILevel"))
        {
            origin = strchr(tmp, ' ');
            level = atoi(origin);
            break;
        }
    }

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
    char tmp[N_CONFS+1];
    FILE *f = fopen(FILE_NAME, "r"), *nf = fopen("tmp.txt", "a+");

    fseek(f, 0, SEEK_SET);
    fgets(tmp, N_CONFS+1, f);
    fgets(tmp, N_CONFS+1, f);
    fprintf(nf, "DefaultTypeP %c %c\n", p.player1, p.player2);
    fprintf(nf, tmp);

    fclose(f);
    fclose(nf);

    remove(FILE_NAME);
    rename("tmp.txt", FILE_NAME);
}

void setDefaultAILevel(int level)
{
    char tmp[N_CONFS+1];
    FILE *f = fopen(FILE_NAME, "r"), *nf = fopen("tmp.txt", "a+");

    fseek(f, 0, SEEK_SET);
    fgets(tmp, N_CONFS+1, f);
    fprintf(nf, "%s", tmp);
    fprintf(nf, "DefaultAILevel %d", level);
    
    fclose(f);
    fclose(nf);

    remove(FILE_NAME);
    rename("tmp.txt", FILE_NAME);
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
    int c = 'y', want_to_change, choice;
    TypePieces p;
    initializeDefaultSettings();
    while(c == 'y')
    {
        system("cls");
        printDefaultSettings();
        printf("\n");
        printOnNChar("Do you want to change a setting (y/n) : ", ROW_TEXT, 0);
        c = getchar();
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
            printOnNChar("4- Change to {x, o}", ROW_TEXT, 4);
            printf("\n");
            printOnNChar("5- Change to {+, o}", ROW_TEXT, 4);
            printf("\n\n");
            want_to_change = 1;
            while(want_to_change)
            {
                choice = get_change_choice();
                switch(choice)
                {
                    case Beginner:
                    case Intermediate:
                    case Advanced:
                        setDefaultAILevel(choice);
                        want_to_change = 0;
                        break;
                    case 4:
                        p.player1 = 'x';
                        p.player2 = 'o';
                        setDefaultTypePieces(p);
                        want_to_change = 0;
                        break;
                    case 5:
                        p.player1 = '+';
                        p.player2 = 'o';
                        setDefaultTypePieces(p);
                        want_to_change = 0;
                        break;
                    default:
                        want_to_change = 1;
                }
            }
        }
    }
}