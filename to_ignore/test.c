#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

int main()
{
    char word[N+1] = "";
    int len_word;

    printf("Please, give a word : ");
    fgets(word, N+1, stdin);
    len_word = strlen(word);
    if(word[len_word-1] == '\n')
        word[len_word-1] = 0;
    else
        while(getchar() != '\n');
    
    --len_word;
    for(int len_subword = 1; len_subword <= len_word; ++len_subword)
    {
        for(int i = 0; i+len_subword-1 < len_word; ++i)
        {
            for(int j = i; j <= i+len_subword-1; ++j)
                printf("%c", word[j]);
            printf("\n");
        }
    }

    return EXIT_SUCCESS;
}