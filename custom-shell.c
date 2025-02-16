#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

int readAndExecute();
void runShell();
void intHandler(int signal);

int main()
{
    struct sigaction sa;
    sa.sa_handler = intHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    runShell();
    return 0;
}

void runShell()
{
    int EXITED = 0;
    while (EXITED == 0)
        EXITED = readAndExecute();
}

void intHandler(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    runShell();
}