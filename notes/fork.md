```
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int x = 100;
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        perror("Failed to create a fork!\n");
    }
    else if (pid == 0)
    {
        printf(" value of x in child is: %d\n", x);
        x = 101;
    }
    else
    {
        pid_t rc = wait(NULL);
        x = 102;
    }

    printf("x: %d\n", x);

    return 0;
}
```

`
----Output----

value of x in child is: 100
x: 101
x: 102
`

**Conclusion**
A child process makes an exact copy of variables, functions, and memory of the parent process, when the fork system call is called. But after that, change in one process doesn't affect anything in the other process.



```
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    pid_t pid;

    int fd;
    fd = open("./demo.txt", O_CREAT | O_WRONLY | O_TRUNC);

    pid = fork();

    if (pid < 0)
    {
        perror("Failed to create a fork!\n");
    }
    else if (pid == 0)
    {
        printf(" value of fd in child is: %d\n", fd);
        write(fd, "hello from child.\n", 18);
    }
    else
    {
        printf(" value of fd in parent is: %d\n", fd);
        write(fd, "hello from parent.\n", 19);
    }

    return 0;
}
```

`
----Output----

value of fd in parent is: 3
value of fd in child is: 3
`

**Conclusion**
Both the child and parent processes have access to the same file decriptors. Meaning both can affect the same file. In such cases, it is better to use wait system call for better Synchronization.


