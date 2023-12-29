#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD WINAPI print_once(void* pString)
{
    printf("%s\n", (char*)pString);
    Sleep(3000);

    return 0;
}

DWORD WINAPI print_twice(void* pString)
{
    printf("%s", (char*)pString);
    printf("%s\n", (char*)pString);
    Sleep(3000);

    return 0;
}

int main(void)
{
    HANDLE thread1, thread2;

    // make threads
    thread1 = CreateThread(NULL, 0, print_once, "Foo", 0, NULL);
    thread2 = CreateThread(NULL, 0, print_twice, "Bar", 0, NULL);

    // wait for them to finish
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    return 0;
}