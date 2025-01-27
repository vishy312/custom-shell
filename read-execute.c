#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int executeCommand(char *args[]);
char **parseTokens(char **tokens);
char *readCommand();
char **tokenize(char *commandStr);

int readAndExecute()
{
    char *currDir = (char *)malloc(sizeof(char) * 100);
    getcwd(currDir, 100);
    if (currDir == NULL)
    {
        perror("failed to get current directory.");
    }
    else
    {
        printf("%s%s", currDir, ">");
    }
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