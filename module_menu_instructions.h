#ifndef MENUINSTRUCTIONSH
#define MENUINSTRUCTIONSH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "module_shared.h"

enum Level {Beginner=1, Intermediate, Advanced};

void welcome();
void printMenu();
void printInstructions();
int get_menu_choice();

#endif