#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void a(){
    FILE *fichier = fopen("fihcier.txt", "w");

    fprintf(fichier, "Line 1");
    
    fclose(fichier);
} 

int main()
{
    a();

    return EXIT_SUCCESS;
}