#include "../include/module_file.h"

void deleteLine(char* file_name, int n)
{
    char c = 1;
    int i;
    FILE *f = fopen(file_name, "r"), *nf = fopen("tmp.txt", "a+");

    fseek(f, 0, SEEK_SET);
    for(i = 1; c != EOF; ++i)
    {
        while( (c=fgetc(f)) != EOF)
        {
            if(i != n)
                fputc(c, nf);
            if(c == '\n')
                break;
        }
    }
    fclose(f);
    fclose(nf);

    remove(file_name);
    rename("tmp.txt", file_name);
}

void changeLine(char* file_name, int n, char* string)
{
    char c = 1;
    int i;
    FILE *f = fopen(file_name, "r"), *nf = fopen("tmp.txt", "a+");

    fseek(f, 0, SEEK_SET);
    for(i = 1; c != EOF; ++i)
    {
        while( (c=fgetc(f)) != EOF)
        {
            if(i != n)
                fputc(c, nf);
            if(c == '\n')
                break;
        }
        if(i == n)
            fputs(string, nf);
    }
    fclose(f);
    fclose(nf);

    remove(file_name);
    rename("tmp.txt", file_name);
}

int exist(char* file_name)
{
    FILE *f = fopen(file_name, "r");

    if(f != NULL)
    {
        fclose(f);
        return 1;
    }

    return 0;
}