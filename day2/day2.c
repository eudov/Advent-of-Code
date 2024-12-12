#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        perror("Unable to open file!");
        exit(1);
    }

    char chunk[128];

    size_t len = sizeof(chunk);
    char *line = malloc(len);
    if (line == NULL)
    {
        perror("Unable to allocate memory for the line buffer.");
        exit(1);
    }

    line[0] = '\0';

    while (fgets(chunk, sizeof(chunk), fp) != NULL)
    {
        size_t len_used = strlen(line);
        size_t chunk_used = strlen(chunk);

        if (len - len_used < chunk_used)
        {
            len *= 2;
            if ((line = realloc(line, len)) == NULL)
            {
                perror("Unable to reallocate memory for the line buffer.");
                free(line);
                exit(1);
            }
        }

        strncpy(line + len_used, chunk, len - len_used);
        len_used += chunk_used;

        if (line[len_used - 1] == '\n')
        {
            fputs(line, stdout);
            fputs("|*\n", stdout);
            line[0] = '\0';
        }

        fputs(chunk, stdout);
    }

    fclose(fp);
    free(line);

    return 0;
}