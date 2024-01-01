#include "module_menu_instructions.h"


/*void welcome()
{
    printOnNChar("WELCOME", ROW_TEXT, 0);
    Sleep(3000);
}*/
void welcome()
{
    system("cls"); // Effacer l'écran

    printf("\n\n");
    printOnNChar("  * WELCOME TO PUISSANCE 4 *  ", 30, 0);
    printf("\n\n");

    printf("       Loading: ");

    int loadingBarWidth = 100;  // La largeur de la barre de chargement
    for (int i = 0; i <= loadingBarWidth; ++i)
    {
        Sleep(15);  // Attendre un court moment pour afficher la progression

        printf("\r       [");
        printNChar('#', i);
        printNChar(' ', loadingBarWidth - i);
        printf("] %d%%", i * 100 / loadingBarWidth);
        fflush(stdout);  // Rafraîchir la sortie pour afficher la barre de progression

        if (i == loadingBarWidth)
            printf("\n");  // Nouvelle ligne une fois la barre de chargement complète
    }
    printf("\n\n");
    printOnNChar("   GET READY !!!!!!  ", 30, 0);
    Sleep(1000);  // Attendre un moment avant de terminer

    system("cls"); // Effacer l'écran à la fin du chargement
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
