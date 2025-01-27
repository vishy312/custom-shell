#include <stdio.h>

int executeCommand(char *args[]);
char **parseTokens(char **tokens);
char *readCommand();
char **tokenize(char *commandStr);

int readAndExecute()
{
    char *command = readCommand();
    if (command == NULL)
    {
        return 1;
    }
    char **tokens = tokenize(command);
    char **parsedTokens = parseTokens(tokens);
    executeCommand(parsedTokens);

    return 0;
}