#include <stdio.h>

int main()
{
    char c;
    int n;

    scanf("%d", &n);
    c = getchar();

    printf("%d - %d\n", n, c);

    return 0;
}