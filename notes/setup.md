## How a shell actually works
- It consists of three major phases; Read, Parse, and Execute.
- Initially the command is being read from the command line.
- Then it gets parsed.
- Linux mostly deals with two things; Files and Process. The filepath corresponding to the command is searched and then the command gets replaced with the file path. This all is a part of parsing phase.
- In Execute phase, the shell uses `fork()` system call to create a chile process. Then the command gets executed in that child process. Then the shell uses `wait()` system call to terminate the process.
  
## Process ID
- A process is program currently in execution.
- Process ID (PID) is a unique identifier attached with a process.
- in C, PID of a process can be available from `unistd.h` library. It's data type is `pid_t`. Which is a signed integer type.

## fork() return values
- PID of child process in the parent process.
- 0 in the child process.
- -1 if failed to create the child process.