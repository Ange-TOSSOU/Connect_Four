#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

DWORD WINAPI get_choice(void* pVar)
{
    char c;
    int stop = 0;
    printf("Make a choice : ");

    *(char*)pVar = getchar();

    return 0;
}

int main(void)
{
    char c1 = 0, c2 = ' ';
    int i = 0;
    HANDLE thread;

    printf("BEFORE : %d %d\n", c1, c2);

    // make threads
    thread = CreateThread(NULL, 0, get_choice, &c1, 0, NULL);

    while(c1 == 0 && i < 200)
    {
        Sleep(100);
        if(i%50 == 0)
            printf("\nMake a choice (il reste %d s) : ", 20-i/10);
        ++i;
    }

    if(c1 == 0)
    {
        printf("\nTime out, press any key to continue : ");
        WaitForSingleObject(thread, INFINITE);
    }
    //TerminateThread(thread, 0x0);
    //CloseHandle(thread);
    
    printf("\nBOUM : ");
    c2 = getchar();

    printf("AFTER : %d %d\n", c1, c2);

    //if(c == 0)
    // wait for them to finish
    //WaitForSingleObject(thread, INFINITE);

    return 0;
}