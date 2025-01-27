#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
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
    }
}
