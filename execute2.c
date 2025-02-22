#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

char **tokenize2(char *commandStr, int *length, char *delimeter);
void multipleExecution(char *command);
void parallelExecution(char *command);
void redirections(char *command);
void builtinExecution(char *args[]);
void *threadExecution(void *vargp);

void execute2(char *command)
{
    multipleExecution(command);
}

void multipleExecution(char *command)
{
    char *dels = ";";
    int length = 0;

    char **subcommands = tokenize2(command, &length, dels);
    for (int i = 0; i < length; i++)
    {
        parallelExecution(subcommands[i]);
    }
}

void parallelExecution(char *command)
{
    char *dels = "&";
    int length = 0;

    char **subcommands = tokenize2(command, &length, dels);
    if (length > 0)
    {
        redirections(subcommands[0]);
    }

    pthread_t threads[length - 1];

    for (int i = 1; i < length; i++)
    {
        void *com = (void *)subcommands[i];
        pthread_create(&threads[i - 1], NULL, threadExecution, com);
    }

    for (int i = 0; i < length - 1; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

void *threadExecution(void *vargp)
{
    char *command = (char *)vargp;
    redirections(command);
    free(command);
    pthread_exit(NULL);
}

void redirections(char *command)
{
    char *arrowDel = ">";
    char *pipeDel = "|";
    int arrowLen = 0;
    char **subcommands = tokenize2(command, &arrowLen, arrowDel);

    int pipeLen = 0;
    char **pipecommands = tokenize2(subcommands[0], &pipeLen, pipeDel);

    if (pipeLen == 1 && arrowLen == 1)
    {
        pid_t pid;
        pid = fork();

        if (pid < 0)
        {
            perror("Failed! to create a fork!\n");
        }
        else if (pid == 0)
        {
            int argsLength = 0;
            char **args = tokenize2(pipecommands[0], &argsLength, " \t\r\n");

            int exec_val = execvp(args[0], args);

            if (exec_val == -1)
            {
                perror("Command Execution Failed!\n");
            }
        }
        waitpid(pid, NULL, 0);
    }
    else
    {

        if (arrowLen > 1)
        {
            char *outfile = subcommands[1];
            while (*outfile == ' ')
                outfile++;

            int len = strlen(outfile);
            while (len > 0 && (outfile[len - 1] == ' ' || outfile[len - 1] == '\n'))
            {
                outfile[--len] = '\0';
            }

            subcommands[1] = outfile;
        }
        printf("%d\n", pipeLen - 1);
        int pipes[pipeLen - 1][2];
        for (int i = 0; i < pipeLen - 1; i++)
        {
            if (pipe(pipes[i]) == -1)
            {
                perror("Pipe creation failed!");
                exit(1);
            }
        }

        pid_t pids[pipeLen];

        for (int i = 0; i < pipeLen; i++)
        {
            pids[i] = fork();

            if (pids[i] < 0)
            {
                perror("Failed to create process fork!");
            }
            else if (pids[i] == 0)
            {
                for (int j = 0; j < pipeLen - 1; j++)
                {
                    if (j != i - 1)
                        close(pipes[j][0]);
                    if (j != i)
                        close(pipes[j][1]);
                }

                if (i > 0)
                {
                    if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
                    {
                        perror("Failed to duplicate stdin");
                        exit(1);
                    }
                    close(pipes[i - 1][0]);
                }

                if (i < pipeLen - 1)
                {
                    if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
                    {
                        perror("Failed to duplicate stdout");
                        exit(1);
                    }
                    close(pipes[i][1]);
                }

                if (i == pipeLen - 1)
                {
                    if (arrowLen > 1)
                    {
                        int flags;
                        if (strstr(command, ">>") != NULL)
                        {
                            flags = O_WRONLY | O_CREAT | O_APPEND;
                        }
                        else
                        {
                            flags = O_WRONLY | O_CREAT | O_TRUNC;
                        }

                        int fd = open(subcommands[1], flags, 0644);
                        if (fd == -1)
                        {
                            perror("Output file Not opened correctly!");
                        }

                        if (dup2(fd, STDOUT_FILENO) == -1)
                        {
                            perror("Failed to duplicate stdout");
                            exit(1);
                        }

                        close(fd);
                    }
                }

                int argsLength = 0;
                char **args = tokenize2(pipecommands[i], &argsLength, " \t\r\n");
                int exec_val = execvp(args[0], args);
                if (exec_val == -1)
                {
                    perror("Failed to execute the command");
                    exit(1);
                }
            }
        }

        for (int i = 0; i < pipeLen - 1; i++)
        {
            close(pipes[i][0]);
            close(pipes[i][1]);
        }
        for (int i = 0; i < pipeLen; i++)
        {
            waitpid(pids[i], NULL, 0);
        }
    }
}
char **tokenize2(char *commandStr, int *length, char *delimeter)
{
    // we need to convert char * type to char[] to avoid segmentation error.
    char command[200];
    strcpy(command, commandStr);

    int len = strlen(command);
    char *token = strtok(command, delimeter);

    int capacity = 2;
    char **tokens = (char **)malloc(sizeof(char *) * capacity);
    if (tokens == NULL)
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    int i = 0;

    while (token != NULL)
    {
        if (i >= capacity)
        {
            // Resize the tokens array
            capacity *= 2;
            tokens = realloc(tokens, sizeof(char *) * capacity);
            if (tokens == NULL)
            {
                perror("Failed to reallocate memory");
                exit(EXIT_FAILURE);
            }
        }

        tokens[i] = malloc(strlen(token) + 1);
        if (tokens[i] == NULL)
        {
            perror("Failed to allocate memory for token");
            exit(EXIT_FAILURE);
        }

        // assigning the token(s) to the tokens array.
        strcpy(tokens[i], token);
        i++;
        token = strtok(NULL, delimeter);
    }
    *length = i;
    // setting the pointer to null
    tokens[i] = NULL;

    return tokens;
}

void builtinExecution(char *args[])
{

    if (args[1] == NULL)
    {
        perror("No filepath defined!");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("Failed to change directory!");
        }
    }
}