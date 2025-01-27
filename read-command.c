#include <stdio.h>
#include <string.h>

char *readCommand()
{
    char *lineptr = NULL;
    size_t n = 10;
    getline(&lineptr, &n, stdin);

    int cmpInt = strcmp(lineptr, "exit\n");
    if (cmpInt == 0)
    {
        return NULL;
    }

    return lineptr;
}