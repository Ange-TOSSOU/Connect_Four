#include "module_file.h"

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

void addLine(char* file_name, int** grid, int row_g, int col_g, char c)
{
    int i, j;
    FILE *f = fopen(file_name, "a+");

    for(i = 0; i < row_g; ++i)
    {
        for(j = 0; j < col_g; ++j)
        {
            if(i == 0 && j == 0)
                fprintf(f, "%d", grid[i][j]);
            else
                fprintf(f, " %d", grid[i][j]);
        }
    }

    if(c == '\n')
        fprintf(f, "%c", c);

    fclose(f);
}