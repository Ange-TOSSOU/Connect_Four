#include "module_shared.h"

void printNChar(char c, int n)
{
    int i = 0;

    while(i < n)
    {
        printf("%c", c);
        ++i;
    }
}

void printOnNChar(char *string, int n, int margin_to_add)
{
    int i = 0, j = 0, flag = 1, len = strlen(string), row, ret, l_margin = margin_to_add;
    CONSOLE_SCREEN_BUFFER_INFO w_size;

    ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &w_size);
    if(ret)
    {
        row = w_size.dwSize.X;
        if(row >= n)
            l_margin += (row-n)/2;
    }
    else
    {
        printf("Unable to get the console size.\n");
        exit(EXIT_FAILURE);
    }

    while(i < len)
    {
        if(flag)
        {
            printNChar(' ', l_margin);
            flag = 0;
        }
        if(j < n)
        {
            printf("%c", string[i]);
            ++j;
            ++i;
        }
        else
        {
            j = 0;
            flag = 1;
            printf("\n");
        }
    }
}