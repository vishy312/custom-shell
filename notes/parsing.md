## Parsing

- After tokenization, we need to parse the primary token to its corresponding filepath.
- We need to do this step because the `exec()` function expects the filepath of the program you want to execute as the first token.
- So we will take the first token of the tokens array, concatenate it to the string '/bin/`, and replace the original token with this new string.
- We can use `strcat()` function to do that. but it can only do the concatenation if the first string has enough memory.
- For that we have a workaround.
  ```
    char **parseTokens(char **tokens)
{
    int i = 0;
    while (tokens[i] != NULL)
    {
        if (i == 0)
        {
            int newSize = strlen("/bin/") + strlen(tokens[i]) + 1;
            char *newStr = (char *)malloc(sizeof(char) * newSize);
            strcpy(newStr, "/bin/");
            strcat(newStr, tokens[i]);
            strcpy(tokens[i], newStr);
        }
        i++;
    };
    return tokens;
}
  ```