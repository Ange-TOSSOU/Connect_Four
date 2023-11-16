#include "main.h"

int main()
{
    int want_to_continue = 1, menu_choice;

    welcome();
    while(want_to_continue)
    {
        system("cls");
        printMenu();
        menu_choice = get_menu_choice();
        switch(menu_choice)
        {
            case Play_in_pairs:
                system("cls");
                //printf("Play in pairs\n");
                break;
            case Play_with_ai:
                system("cls");
                //printf("Play with ai\n");
                break;
            case Revisualize_game:
                system("cls");
                //printf("Revisualize a game\n");
                break;
            case Statistics:
                system("cls");
                //printf("Statistiques\n");
                want_to_continue = 1;
                break;
            case Settings:
                system("cls");
                settings();
                want_to_continue = 0;
                break;
            case Instructions:
                system("cls");
                printInstructions();
                want_to_continue = 1;
                break;
            case Quit:
                want_to_continue = 0;
                break;
            default:
                want_to_continue = 1;
        }
        //want_to_continue = 0;
    }
    return EXIT_SUCCESS;
}