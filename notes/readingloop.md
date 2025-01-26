## Reading Loop

**Code**
```
#include <stdio.h>
#include <string.h>

int main() {
    int EXITED = 0;
    char *lineptr = NULL;
    size_t n = 10;
    getline(&lineptr, &n, stdin);
    
    int cmpInt = strcmp(lineptr, "exit\n");
    if(cmpInt == 0){
        EXITED = 1;
    }
    printf("Entered command: %s", lineptr);
    
    while(EXITED == 0){
        char *lineptrLoop = NULL;
        size_t nLoop = 10;
        getline(&lineptrLoop, &nLoop, stdin);
        
        int compIntLoop = strcmp(lineptrLoop, "exit\n");
        if(compIntLoop == 0){
            EXITED = 1;
            break;
        }
        
        printf("Entered command: %s", lineptrLoop);
    }

    return 0;
}
```

**Comments/Notes**
- The requirement here is to be able to read a line from commandline until the user types `exit` and enter.
- To read a line from command line we use `getline()` function from `stdio.h` library.
 ```
    char *lineptr = NULL;
    size_t n = 10;
    getline(&lineptr, &n, stdin);
```

- After reading a line, each time the input line will be compared with the string `exit\n`.
- To do that, we can use the `strcmp()` function from `string.h` library. This function compare two strings and returns an integer. The integer will be `0` if both the strings are equal.  
  ```
  int cmpInt = strcmp(lineptr, "exit\n");
  ```

- At the start of the main function, we've initialized a flag that we will use for loop's condition. If at any point, user enters the xommand `exit`, the flag `EXITED` will be made 0 and the loop will be exited.
- The step would be to create a separate function for reading command. Its essential for modularization and readability.
  ```
  char *readCommand(){
    char *lineptr = NULL;
    size_t n = 10;
    getline(&lineptr, &n, stdin);
    
    int cmpInt = strcmp(lineptr, "exit\n");
    if(cmpInt == 0){
        return NULL;
    }
    
    return lineptr;
}
  ```

- The code in the main function will look something like this.
```
int main(){
    int EXITED = 0;
    char *command = readCommand();
    if (command == NULL)
    {
        return 0;
    }
    printf("Entered command: %s", command);

    while (EXITED == 0)
    {
        char *commandLoop = readCommand();
        if (commandLoop == NULL)
        {
            EXITED = 1;
            break;
        }

        printf("Entered command: %s", commandLoop);
    }
}

```

