*This project has been created as part of the 42 curriculum by adores.*

# Pipex

## Description
**Pipex** is a project that mimics the behavior of the shell pipeline operator (`|`). The program handles the redirection of standard input and output between two commands using a pipe, allowing the output of the first command to serve as the input for the second. 

---

## Instructions

Running this command:
```bash
./pipex infile "cmd1" "cmd2" outfile
```

Is functionally equivalent to:
```bash
< infile cmd1 | cmd2 > outfile
```

## Error Handling

If the number of arguments is incorrect, the program writes an error message to stderr.

If a command is not found, the program prints a "command not found" error and exits with code 127.

System call failures (like pipe or fork errors) trigger perror and terminate the program to ensure stability.

## Technical Details

**Command Execution Logic**

The program parses the environment variables (envp) to locate the PATH. It then checks each directory in the path to find the correct executable for the provided command.

Child 1: Opens the input file, redirects it to stdin, redirects the pipe's write-end to stdout, and executes the first command.

Child 2: Opens/creates the output file, redirects the pipe's read-end to stdin, redirects the output file to stdout, and executes the second command.


## Project Structure

```
pipex/
├── pipex.c         # Main program logic and process management
├── utils.c         # Path resolution and string utilities
├── utils2.c        # File descriptor cleanup and error handling
├── pipex.h         # Header file with function prototypes
├── Makefile        # Build automation
└── libft/          # Custom C library dependency
```
