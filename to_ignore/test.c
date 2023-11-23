#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void a(){
    FILE *fichier = fopen("fihcier.txt", "w");

    fprintf(fichier, "1 2 3\n4 5 6\n7 8 9");
    
    fclose(fichier);
}

void b(){
    char c = 1;
    int a, i = 0;
    FILE *fichier = fopen("fihcier.txt", "r");

    while(c != EOF)
    {
        ++i;
        fscanf(fichier, "%d", &a);
        printf("%d\n", a);
        if(i == 3)
        {
            i = 0;
            c = fgetc(fichier);
        }
    }

    fclose(fichier);
}

int main()
{
    a();
    b();

    return EXIT_SUCCESS;
}