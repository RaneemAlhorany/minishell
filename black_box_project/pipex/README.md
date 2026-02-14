*This project has been created as part of the 42 curriculum by ralhoura.*

# Pipex

## Description

**Pipex** is a Unix system programming project developed as part of the 42 curriculum.
It recreates the behavior of shell pipelines using low-level system calls.

The project focuses on understanding:
- Process creation using `fork`
- Inter-process communication with `pipe`
- File descriptor redirection via `dup2`
- Command execution using `execve`
- Proper error handling and memory management

### Mandatory Part
Reproduces the behavior of the shell command:

    < infile cmd1 | cmd2 > outfile

### Bonus Part
Supports an unlimited number of commands chained together:

    < infile cmd1 | cmd2 | ... | cmdN > outfile

---

## Instructions

### Requirements
- Unix-based OS (Linux / macOS)
- C compiler (`cc`)
- `make`

### Compilation

Mandatory version:
    make

Bonus version:
    make bonus

This generates the executable:
    ./pipex

---

## Usage

### Mandatory
    ./pipex infile "cmd1" "cmd2" outfile

Example:
    ./pipex input.txt "ls -l" "wc -l" output.txt

### Bonus
    ./pipex infile "cmd1" "cmd2" ... "cmdN" outfile

Example:
    ./pipex input.txt "cat" "grep error" "wc -l" output.txt

---

## Technical Overview

- Each command runs in its own process.
- Pipes connect the output of one command to the input of the next.
- The parent process manages:
  - Pipe creation
  - Forking
  - Closing file descriptors
  - Waiting for child processes

### System Calls Used
- `fork`
- `pipe`
- `dup2`
- `execve`
- `waitpid`
- `open` / `close`

---

## Error Handling & Memory Management

- All file descriptors are properly closed.
- All allocated memory is freed.
- Dedicated error exit functions are used.
- No memory leaks or double frees.

---

## Resources

### References
- man fork
- man pipe
- man dup2
- man execve
- man waitpid
- GNU C Library Documentation
- Advanced Unix Programming references

### AI Usage

AI was used as a learning assistant for:
- Explaining system calls
- Reviewing logic and structure
- Improving documentation clarity

AI was not used to generate final code or bypass understanding.
All implementation and debugging were done manually.

---

## Notes

- Fully compliant with 42 norms
- Bonus replaces mandatory pipeline logic
- Tested with multiple edge cases

---