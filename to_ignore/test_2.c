#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

void subword(char *mot, int pos, char *subw, int taille)
{
    if(pos = strlen(mot)){
        subw[taille] = '\0';
        printf("%s\n", subw);
        return;
    }

    subword(mot, pos+1, subw, taille);
    subw[taille] = mot[pos];
    subword(mot, pos+1, subw, taille+1);
}

int main()
{
    char word[N+1] = "", subw[N+1] = "";
    int len_word, *tab, nb_subwords;

    printf("Please, give a word : ");
    fgets(word, N+1, stdin);
    len_word = strlen(word);
    if(word[len_word-1] == '\n')
        word[len_word-1] = 0;
    else
        while(getchar() != '\n');
    
    --len_word;

    nb_subwords = 1 << len_word;
    subword(word, 0, subw, 0);
    

    return EXIT_SUCCESS;
}