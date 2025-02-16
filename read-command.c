#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *readCommand()
{
    char *lineptr = NULL;
    size_t n = 10;
    if (getline(&lineptr, &n, stdin) == -1)
    {
        return NULL;
    }

    int cmpInt = strcmp(lineptr, "exit\n");
    if (cmpInt == 0)
        return NULL;

    return lineptr;
}