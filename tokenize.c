#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void splitArray(
    char **array,
    int length,
    int splitIndex,
    char *(*subarray1)[],
    int *length1,
    char *(*subarray2)[],
    int *length2);

char **tokenize(char *commandStr, int *length)
{
    // we need to convert char * type to char[] to avoid segmentation error.
    char command[100];
    strcpy(command, commandStr);

    // to remove unwanted newline character at the end
    int len = strlen(command);
    if (len > 0)
        command[len - 1] = '\0';

    // actual tokenization operation
    char *delimiter = " \t\n\r";
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

        // assigning the token(s) to the tokens array.
        strcpy(tokens[i], token);
        i++;
        token = strtok(NULL, " ");
    }
    *length = i;
    // setting the pointer to null
    tokens[i] = NULL;

    return tokens;
}