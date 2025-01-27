## Tokenization

- After reading the input command, the next step is to create tokens out of it.
- It's because the exec functions take array of strings as input.
- to create tokens we will use the `strtok()`  function from `string.h` library.
  ```
    char **tokenize(char *commandStr)
{
    // we need to convert char * type to char[] to avoid segmentation error.
    char command[100];
    strcpy(command, commandStr);

    // to remove unwanted newline character at the end
    int len = strlen(command);
    if (len > 0)
    {
        command[len - 1] = '\0';
    }

    // actual tokenization operation
    char *token = strtok(command, " ");

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
        token = strtok(NULL, " ");
    }

    // setting the pointer to null
    tokens[i] = NULL;

    return tokens;
}
  ```


- the strtok() method gives segmentation error when the argument is of the type char*. That's because char* types are readonly type strings. We can't modify them. So, we need to convert it char[] type before the tokenization process.

- The input from the getline() function has a newline character at the end. This is unnecessary. So we need to remove it before the tokenization process.

- We save the result of the strtok() function in the `token` pointer variable. But the function returns only the first token. to get all the tokens we need to run a while loop and store all the tokens in a dynamic array, which is initialized using the malloc() function.

- After that we can return the resulting tokens.