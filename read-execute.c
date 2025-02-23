#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char **parseTokens(char **tokens);
char *readCommand();
char **tokenize2(char *commandStr, int *length, char *delimeter);
void batchExecution(char *filepath);

void execute2(char *command);

int readAndExecute()
{
    printf("dash> ");

    char *command = readCommand();
    if (command == NULL)
        return 1;

    int length = 0;
    char **tokens = tokenize2(command, &length, " \t\r\n");

    if (length == 0)
    {
        return 0;
    }

    if (strcmp(tokens[0], "./dash") == 0)
    {
        if (length == 2)
        {
            batchExecution(tokens[1]);
        }
        else
        {
            perror("Must use one and only one file for batch execution!");
        }
    }
    else
    {
        execute2(command);
    }

    return 0;
}

void batchExecution(char *filepath)
{
    char *filename = filepath;
    FILE *file = fopen(filename, "r");
    char line[256];

    if (file != NULL)
    {
        while (fgets(line, sizeof(line), file))
        {
            execute2(line);
        }
    }
    else
    {
        fprintf(stderr, "Unable to open file!\n");
    }
}