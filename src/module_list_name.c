#include "../include/module_list_name.h"


Elementn* cleanList_Name(Elementn* list)
{
  Elementn *previous = NULL, *cur = list;

  while(cur != NULL)
  {
    previous = cur;
    cur = cur->next;
    free(previous);
  }

  return cur;
}

Elementn* createElement_Name(char* name)
{
  Elementn* e = (Elementn*)malloc(sizeof(Elementn));
  strcpy(e->name, name);
  e->next = NULL;

  return e;
}

Elementn* pushElement_Name(Elementn* list, char* name)
{
    char name_1[N+1] = "", name_2[N+1] = "";
    int i;
    Elementn *e = createElement_Name(name), *cur1, *cur2;

    if(findElement_Name(list, name))
        return list;
    
    if(list == NULL)
        list = e;
    else if(list->next == NULL)
    {
        strcpy(name_1, e->name);
        for(i = 0; name_1[i]; ++i)
            name_1[i] = (char)tolower(name_1[i]);
        strcpy(name_2, list->name);
        for(i = 0; name_2[i]; ++i)
            name_2[i] = (char)tolower(name_2[i]);
        if(strcmp(name_1, name_2) < 0)
        {
            e->next = list;
            list = e;
        }
        else
            list->next = e;
    }
    else
    {
        cur1 = list;
        cur2 = list->next;
        while(cur2 != NULL)
        {
            strcpy(name_1, e->name);
            for(i = 0; name_1[i]; ++i)
                name_1[i] = (char)tolower(name_1[i]);
            strcpy(name_2, cur2->name);
            for(i = 0; name_2[i]; ++i)
                name_2[i] = (char)tolower(name_2[i]);
            if(strcmp(name_1, name_2) < 0)
            {
                e->next = cur2;
                cur1->next = e;
                break;
            }
            cur1 = cur2;
            cur2 = cur2->next;
        }
        if(cur2 == NULL)
            cur1->next = e;
    }

    return list;
}

Elementn* findElement_Name(Elementn* list, char* name)
{
  char name_1[N+1] = "", name_2[N+1] = "";
  int i;
  while(list != NULL)
  {
    strcpy(name_1, list->name);
    for(i = 0; name_1[i]; ++i)
        name_1[i] = (char)tolower(name_1[i]);
    strcpy(name_2, name);
    for(i = 0; name_2[i]; ++i)
          name_2[i] = (char)tolower(name_2[i]);
    if(strcmp(list->name, name) == 0)
      return list;

    list = list->next;
  }

  return NULL;
}

/*Elementn* popElement(Elementn* list, int a)
{
  Elementn *previous = NULL, *cur = list;

  if(cur != NULL)
  {
    if(cur->value == a)
    {
      list = cur->next;
      free(cur);
    }
    else
    {
      while( (cur != NULL) && (cur->value != a) )
      {
        previous = cur;
        cur = cur->next;
      }
      if(cur != NULL)
      {
        previous->next = cur->next;
        free(cur);
      }
    }
  }
  
  return list;
}

void printList(Elementn* list)
{
  int start = 1;
  
  while(list != NULL)
  {
    if(start)
    {
      printf("{%d}", list->value);
      start = 0;
    }
    else
      printf(" -> {%d}", list->value);

    list = list->next;
  }

  if(start)
    printf("The list is empty.");

  printf("\n");
}*/