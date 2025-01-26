#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int executeCommand(char *args[]);
char parseArgs(char *args[]);
char *readCommand();

int main()
{
    // Reading loop
    int EXITED = 0;
    char *command = readCommand();
    if (command == NULL)
    {
        return 0;
    }
    printf("Entered command: %s", command);

    while (EXITED == 0)
    {
        char *commandLoop = readCommand();
        if (commandLoop == NULL)
        {
            EXITED = 1;
            break;
        }

        printf("Entered command: %s", commandLoop);
    }

    // parsing

    char *args[] = {"ls", "-l", NULL};

    char *parsedArgs[] = parseArgs(args);

    // execution
    executeCommand(parsedArgs);

    return 0;
}