#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void splitArray(
    char **array,
    int length,
    int splitIndex,
    char *(*subarray1)[],
    int *length1,
    char *(*subarray2)[],
    int *length2);

void splitCommands(
    char **array,
    int length,
    int splitIndex,
    char *(*command1)[],
    int *length1,
    char *(*command2)[],
    int *length2);

int redirection(char *args[], int length, int splitIndex, int append);
int piping(char *args[], int length, int splitIndex);
void parallelExecution(char *args[], int length, int splitIndex);
void multipleExecution(char *args[], int length, int splitIndex);

int executeCommand(char *args[], int length)
{
    for (int j = 0; j < length; j++)
    {

        if (strcmp(args[j], ">") == 0)
        {
            if (j == 0)
            {
                perror("Redirection without a command is not allowed");
                return 0;
            }

            redirection(args, length, j, 0);

            return 0;
        }
        else if (strcmp(args[j], ">>") == 0)
        {
            if (j == 0)
            {
                perror("Redirection without a command is not allowed");
                return 0;
            }

            redirection(args, length, j, 1);
            return 0;
        }
        else if (strcmp(args[j], "|") == 0)
        {
            if (j == 0)
            {
                perror("Piping without a command is not allowed");
                return 0;
            }
            piping(args, length, j);
            return 0;
        }
        else if (strcmp(args[j], ";") == 0)
        {
            parallelExecution(args, length, j);
            return 0;
        }
        else if (strcmp(args[j], "&") == 0)
        {
            multipleExecution(args, length, j);
            return 0;
        }
    }

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

void multipleExecution(char *args[], int length, int splitIndex)
{
    int length1 = splitIndex + 1;
    int length2 = length - splitIndex;
    char *command1[length1];
    char *command2[length2];

    splitCommands(args, length, splitIndex, &command1, &length1, &command2, &length2);

    pid_t pid1;
    pid1 = fork();

    if (pid1 < 0)
    {
        perror("Failed to create process fork!");
    }
    else if (pid1 == 0)
    {
        int exec_val = execvp(command1[0], command1);
        if (exec_val == -1)
        {
            perror("Failed to execute the command");
            exit(1);
        }
    }
    waitpid(pid1, NULL, 0);

    pid_t pid2;
    pid2 = fork();

    if (pid2 < 0)
    {
        perror("Failed to create process fork!");
    }
    else if (pid2 == 0)
    {
        int exec_val2 = execvp(command2[0], command2);
        if (exec_val2 == -1)
        {
            perror("Failed to execute the command");
            exit(1);
        }
    }
    waitpid(pid2, NULL, 0);
}

void parallelExecution(char *args[], int length, int splitIndex)
{
    int length1 = splitIndex + 1;
    int length2 = length - splitIndex;
    char *command1[length1];
    char *command2[length2];

    splitCommands(args, length, splitIndex, &command1, &length1, &command2, &length2);

    pid_t pid1;
    pid1 = fork();

    if (pid1 < 0)
    {
        perror("Failed to create process fork!");
    }
    else if (pid1 == 0)
    {
        int exec_val = execvp(command1[0], command1);
        if (exec_val == -1)
        {
            perror("Failed to execute the command");
            exit(1);
        }
    }

    pid_t pid2;
    pid2 = fork();

    if (pid2 < 0)
    {
        perror("Failed to create process fork!");
    }
    else if (pid2 == 0)
    {
        int exec_val2 = execvp(command2[0], command2);
        if (exec_val2 == -1)
        {
            perror("Failed to execute the command");
            exit(1);
        }
    }
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int piping(char *args[], int length, int splitIndex)
{
    int length1 = splitIndex + 1;
    int length2 = length - splitIndex;
    char *command1[length1];
    char *command2[length2];

    splitCommands(args, length, splitIndex, &command1, &length1, &command2, &length2);

    for (int k = 0; k < length2; k++)
    {
        if (command2[k] != NULL && (strcmp(command2[k], "|") == 0))
        {
            perror("Multiple pipe operators are not allowed.");
            return 0;
        }
    }

    int p[2];
    if (pipe(p) == -1)
    {
        printf("Pipe creation failed!\n");
    }

    pid_t pid1;
    pid1 = fork();

    if (pid1 < 0)
    {
        perror("Failed to create process fork!");
    }
    else if (pid1 == 0)
    {
        close(p[0]);
        if (dup2(p[1], STDOUT_FILENO) == -1)
        {
            perror("Failed to duplicate stdout");
            exit(1);
        }
        close(p[1]);
        int exec_val = execvp(command1[0], command1);
        if (exec_val == -1)
        {
            perror("Failed to execute the command");
            exit(1);
        }
    }

    pid_t pid2;
    pid2 = fork();

    if (pid2 < 0)
    {
        perror("Failed to create process fork!");
    }
    else if (pid2 == 0)
    {
        close(p[1]);
        if (dup2(p[0], STDIN_FILENO) == -1)
        {
            perror("Failed to duplicate stdin");
            exit(1);
        }
        close(p[0]);

        int exec_val2 = execvp(command2[0], command2);
        if (exec_val2 == -1)
        {
            perror("Failed to execute the command");
            exit(1);
        }
    }

    close(p[0]);
    close(p[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int redirection(char *args[], int length, int splitIndex, int append)
{
    int length1 = splitIndex + 1;
    int length2 = length - splitIndex;
    char *subarray1[length1];
    char *subarray2[length2];

    splitArray(args, length, splitIndex, &subarray1, &length1, &subarray2, &length2);

    for (int k = 0; k < length2; k++)
    {
        if ((strcmp(subarray2[k], ">") == 0) || (strcmp(subarray2[k], ">>") == 0))
        {
            perror("Multiple redirection operators are not allowed.");
            continue; // can change to continue
        }
        if (k > 0)
        {
            perror("Redirection to multiple files is not allowed");
            continue;
        }
    }

    // close(1);
    int stdout_backup = dup(STDOUT_FILENO);
    int fd;
    if (append == 0)
    {
        fd = open(subarray2[0], O_WRONLY | O_CREAT | O_TRUNC, 0751);
    }
    else if (append == 1)
    {
        fd = open(subarray2[0], O_WRONLY | O_CREAT | O_APPEND, 0751);
    }

    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);

    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        perror("Failed to create process fork!");
    }
    else if (pid == 0)
    {

        int exec_val = execvp(subarray1[0], subarray1);
        if (exec_val == -1)
        {
            perror("Failed to execute the command");
        }
    }
    else
    {
        wait(NULL);
    }

    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);
}