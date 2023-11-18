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