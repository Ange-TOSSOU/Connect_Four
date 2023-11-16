#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int a;
    char c;

    printf("a : ");
    scanf("%d", &a);
    getchar();

    printf("c : ");
    scanf("%c", &c);
    printf("%c", c);

    

    return EXIT_SUCCESS;
}