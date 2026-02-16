*This project has been created as part of the 42 curriculum by adores.*

# Pipex

## Description
**Pipex** is a project that mimics the behavior of the shell pipeline operator (`|`). The program handles the redirection of standard input and output between two commands using a pipe, allowing the output of the first command to serve as the input for the second. 

---
## Instructions

To compile the project, run:
```bash
make
```

To execute the program, use:
```bash
./pipex    
```

- `<infile>`: Input file to read from
- `<cmd1>`: First command to execute (with its arguments)
- `<cmd2>`: Second command to execute (with its arguments)
- `<outfile>`: Output file to write the result

**Example:**
```bash
./pipex input.txt "grep hello" "wc -l" output.txt
```

This is equivalent to the shell command:
```bash
< input.txt grep hello | wc -l > output.txt
```
## Expected Behavior

The program should behave identically to the shell pipeline:
- Read from `infile`
- Execute `cmd1` with `infile` as input
- Pipe the output of `cmd1` to `cmd2`
- Write the final output to `outfile`

## Error Handling

- **Invalid arguments**: If the number of arguments is incorrect, the program writes an error message to stderr
- **Command not found**: If a command is not found in PATH, the program prints "command not found" and exits with code 127
- **File errors**: If the input file cannot be opened, the program handles the error gracefully
- **System call failures**: Failures in `pipe`, `fork`, or other system calls trigger `perror` and terminate the program

## Technical Details

**Command Execution Logic**

The program uses the following approach:
1. Parses environment variables (`envp`) to locate the PATH
2. Searches each directory in PATH to find the executable for each command
3. Creates a pipe to connect the two processes
4. Forks two child processes:
   - **Child 1**: Opens the input file, redirects it to `stdin`, redirects the pipe's write-end to `stdout`, and executes `cmd1`
   - **Child 2**: Opens/creates the output file, redirects the pipe's read-end to `stdin`, redirects the output file to `stdout`, and executes `cmd2`
5. Parent process waits for both children to complete

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

## Resources

The main resource that contributed to my understanding of this project was discussing its requirements and challenges with my colleagues.

Additional references that were helpful include:

- [Code Vault - Unix Processes Playlist](https://youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&si=8Sa1JQM3rfcQZKib)
- [Pipe System Call - GeeksforGeeks](https://www.geeksforgeeks.org/c/pipe-system-call/)
- [Fork System Call - GeeksforGeeks](https://www.geeksforgeeks.org/c/fork-system-call/)

AI tools were used to assist with the writing and structuring of this README file.

