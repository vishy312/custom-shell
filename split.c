#include <stdlib.h>
#include <stdio.h>

void splitArray(
    char **array,
    int length,
    int splitIndex,
    char *(*subarray1)[],
    int *length1,
    char *(*subarray2)[],
    int *length2)
{
    *length1 = splitIndex + 1;
    *length2 = length - splitIndex - 1;

    for (int i = 0; i < *length1; i++)
    {
        if (i == *length1 - 1)
        {
            (*subarray1)[i] = NULL;
        }
        else
        {
            (*subarray1)[i] = array[i];
        }
    }

    for (int i = 0; i < *length2; i++)
    {
        (*subarray2)[i] = array[i + splitIndex + 1];
    }
}

void splitCommands(
    char **array,
    int length,
    int splitIndex,
    char *(*command1)[],
    int *length1,
    char *(*command2)[],
    int *length2)
{
    *length1 = splitIndex + 1;
    *length2 = length - splitIndex;

    for (int i = 0; i < *length1; i++)
    {
        if (i == *length1 - 1)
        {
            (*command1)[i] = NULL;
        }
        else
        {
            (*command1)[i] = array[i];
        }
        // printf("command1[%d]: %s\n", i, (*command1)[i]);
    }

    for (int i = 0; i < *length2; i++)
    {
        (*command2)[i] = array[i + splitIndex + 1];
        // printf("command2[%d]: %s\n", i, (*command2)[i]);
    }
}