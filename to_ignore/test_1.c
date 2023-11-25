#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

void bin_word(int* tab, int length, int n)
{
    int i;
    for(i = length-1; i >= 0; --i)
    {
        tab[i] = n % 2;
        n = n/2;
    }
}

int main()
{
    char word[N+1] = "", subword[N+1] = "", tmp[2] = "";
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
    tab = calloc(len_word, sizeof(int));

    for(int len_subword = 1; len_subword <= nb_subwords; ++len_subword)
    {
        bin_word(tab, len_word, len_subword);
        strcpy(subword, "");
        for(int i = 0; i < len_word; ++i)
        {
            if(tab[i])
            {
                tmp[0] = word[i];
                strcat(subword, tmp);
            }
        }
        printf("%s\n", subword);
    }

    return EXIT_SUCCESS;
}