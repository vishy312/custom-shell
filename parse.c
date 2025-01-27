#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **parseTokens(char **tokens)
{
    int i = 0;
    while (tokens[i] != NULL)
    {
        if (i == 0)
        {
            int newSize = strlen("/bin/") + strlen(tokens[i]) + 1;
            char *newStr = (char *)malloc(sizeof(char) * newSize);
            strcpy(newStr, "/bin/");
            strcat(newStr, tokens[i]);
            strcpy(tokens[i], newStr);
        }
        i++;
    };
    return tokens;
}