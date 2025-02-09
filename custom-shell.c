#include <stdio.h>

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
    while (EXITED == 0)
        EXITED = readAndExecute();
}