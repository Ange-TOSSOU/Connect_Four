#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void a(){
    FILE *fichier1 = NULL, *fichier2 = NULL;
    char ch = '1';

    fichier1 = fopen("fihcier1.txt", "r");
    fichier2 = fopen("fihcier2.txt", "a+");

    //fprintf(fichier1, "Contenu fichier 1");

    fprintf(fichier2, "Contenu fichier 2\n");
    while((ch = fgetc(fichier1)) != EOF) fputc(ch, fichier2);

    fclose(fichier1);
    fclose(fichier2);

    remove("fihcier1.txt");
    rename("fihcier2.txt", "fihcier1.txt");
} 

int main()
{
    a();

    return EXIT_SUCCESS;
}