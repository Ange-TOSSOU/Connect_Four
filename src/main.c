#include "../include/main.h"

int main()
{
    int want_to_continue = 1, menu_choice;

    welcome("* WELCOME TO PUISSANCE 4 *", "GET READY !!!!!!");
    while(want_to_continue)
    {
        system("cls");
        printMenu();
        menu_choice = get_choice();
        switch(menu_choice)
        {
            case Play_in_pairs:
                welcome("* PLAY IN PAIRS *", "GET READY !!!!!!");
                playGame(Human);
                want_to_continue = 1;
                break;
            case Play_with_ai:
                welcome("* PLAY WITH AI *", "GET READY !!!!!!");
                playGame(AI_Beginner);
                want_to_continue = 1;
                break;
            case Revisualize_game:
                system("cls");
                viewGame();
                want_to_continue = 1;
                break;
            case Statistics:
                welcome("* LOADIND THE STATISTICS *", "DONE");
                printStatistics();
                want_to_continue = 1;
                break;
            case Settings:
                settings();
                want_to_continue = 1;
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