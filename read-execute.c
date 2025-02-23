#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int executeCommand(char *args[], int length);
char **parseTokens(char **tokens);
char *readCommand();
char **tokenize(char *commandStr, int *length);

void execute2(char *command);

int readAndExecute()
{
    printf("dash> ");

    char *command = readCommand();
    if (command == NULL)
        return 1;

    int length = 0;
    char **tokens = tokenize(command, &length);
    // executeCommand(tokens, length);
    execute2(command);

    return 0;
}