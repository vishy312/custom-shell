#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int executeCommand(char *args[])
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        perror("Failed to create a fork!\n");
    }
    else if (pid == 0)
    {
        int exec_val = execvp(args[0], args);

        if (exec_val == -1)
        {
            perror("Command Execution Failed!\n");
        }
    }
    else
    {
        wait(NULL);
        printf("Hello from parent\n");
    }
}

char **parseArgs(char *args[])
{
    char *prefix = "/bin/";

    return args
}

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