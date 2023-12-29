#include "module_menu_instructions.h"

void welcome()
{
    printOnNChar("WELCOME", ROW_TEXT, 0);
    Sleep(3000);
}

void printMenu()
{
    printOnNChar("MENU", ROW_TEXT, 0);
    printf("\n\n");
    printOnNChar("1. Play in pairs", ROW_TEXT, 0);
    printf("\n");
    printOnNChar("2. Play with computer", ROW_TEXT, 0);
    printf("\n");
    printOnNChar("3. Revisualize a game", ROW_TEXT, 0);
    printf("\n");
    printOnNChar("4. Statistics", ROW_TEXT, 0);
    printf("\n");
    printOnNChar("5. Settings", ROW_TEXT, 0);
    printf("\n");
    printOnNChar("6. Instructions", ROW_TEXT, 0);
    printf("\n");
    printOnNChar("7. Exit", ROW_TEXT, 0);
    printf("\n\n");
}

void printInstructions()
{
    printOnNChar("RULES", ROW_TEXT, 0);
    printf("\n");
    printOnNChar("Connect 4 is a game in which the players choose a type of piece and then take turns dropping typed tokens into a 6-row, 7-column vertically suspended grid. The pieces fall straight down, occupying the lowest available space within the column. The objective of the game is to be the first to form a horizontal, vertical, or diagonal line of 4 of one's own tokens.", ROW_TEXT, 4);
    printf("\n\n");
    printOnNChar("HOW TO PLAY", ROW_TEXT, 0);
    printf("\n");
    printOnNChar("- Press an integer between 1 and 7 to fall straight down your piece in the column corresponding.", ROW_TEXT, 4);
    printf("\n");
    printOnNChar("- Press u to go back one step.", ROW_TEXT, 4);
    printf("\n");
    printOnNChar("- Press q to quit the game", ROW_TEXT, 4);
    printf("\n\n");
    printOnNChar("Press any key to go back to the menu : ", ROW_TEXT, 0);
    while(getchar() != '\n');
}

int get_choice()
{
    int c;
    printOnNChar("Make a choice : ", ROW_TEXT, 0);
    scanf("%d", &c);
    while(getchar() != '\n');

    return c;
}