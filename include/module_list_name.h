#ifndef LISTE_NAME_H
#define LISTE_NAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module_shared.h"

struct elementn
{
  char name[ROW_TEXT+1];
  struct elementn *next;
};
typedef struct elementn Elementn;

Elementn* cleanList_Name(Elementn*);
Elementn* createElement_Name(char*);
Elementn* pushElement_Name(Elementn*, char*);
Elementn* findElement_Name(Elementn*, char*);
//Elementn* popElement(Elementn* list, int a);

//void printList(Elementn* list);

#endif