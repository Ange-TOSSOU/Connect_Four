#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
    char c = 0;
    int i = 0;

    printf("So ?!? : ");
    Sleep(3000);
    while(i < 100000000)
        ++i;
    //c = getchar();
    printf("---> %c\n", c);

    return EXIT_SUCCESS;
}