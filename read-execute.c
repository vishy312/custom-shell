#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int executeCommand(char *args[], int length);
char **parseTokens(char **tokens);
char *readCommand();
char **tokenize(char *commandStr, int *length);

int readAndExecute()
{
    printf("custom-shell> ");

    char *command = readCommand();
    if (command == NULL)
        return 1;

    int length = 0;
    char **tokens = tokenize(command, &length);

    // char **parsedTokens = parseTokens(tokens);
    executeCommand(tokens, length);

    return 0;
}