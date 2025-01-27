#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **tokenize(char *commandStr)
{
    char command[100];
    strcpy(command, commandStr);
    int len = strlen(command);
    if (len > 0)
    {
        command[len - 1] = '\0';
    }
    char *token = strtok(command, " ");

    int capacity = 2;
    char **tokens = (char **)malloc(sizeof(char *) * capacity);
    if (tokens == NULL)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    int i = 0;

    while (token != NULL)
    {
        if (i >= capacity)
        {
            // Resize the tokens array
            capacity *= 2;
            tokens = realloc(tokens, sizeof(char *) * capacity);
            if (tokens == NULL)
            {
                perror("Failed to reallocate memory");
                exit(EXIT_FAILURE);
            }
        }

        tokens[i] = malloc(strlen(token) + 1);
        if (tokens[i] == NULL)
        {
            perror("Failed to allocate memory for token");
            exit(EXIT_FAILURE);
        }
        strcpy(tokens[i], token);
        i++;
        token = strtok(NULL, " ");
    }

    tokens[i] = NULL;

    return tokens;
}