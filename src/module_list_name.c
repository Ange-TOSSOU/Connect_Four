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
    Elementn *e = createElement_Name(name), *cur1, *cur2;

    if(findElement_Name(list, name))
        return list;
    
    if(list == NULL)
        list = e;
    else if(list->next == NULL)
    {
        if(strcmp(e->name, list->name) < 0)
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
            if(strcmp(e->name, cur2->name) < 0)
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
  while(list != NULL)
  {
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