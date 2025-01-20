#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int executeCommand(char *args[]);

int main()
{
    char *args[] = {"/bin/ls", "-l", NULL};

    executeCommand(args);

    return 0;
}