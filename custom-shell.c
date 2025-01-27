#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int readAndExecute();
void runShell();

int main()
{
    runShell();
    return 0;
}

void runShell()
{
    int EXITED = 0;
    EXITED = readAndExecute();

    while (EXITED == 0)
    {
        EXITED = readAndExecute();
    }
}