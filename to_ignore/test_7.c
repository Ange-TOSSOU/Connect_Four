void sauvegarder(Joueur p)
{
    int i, j;
    FILE *f = fopen(file_name, "a+");

    for(i = 0; i < ROW_GRID; ++i)
    {
        for(j = 0; j < COL_GRID; ++j)
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