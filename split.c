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