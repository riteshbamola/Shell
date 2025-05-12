# README.md - Documentation for MyCustomShell

# Author: Ritesh Bamola and Team

# MyCustomShell

A custom Unix/Linux shell implementation with support for basic commands, job control, and I/O redirection.

## Features

- Built-in commands: cd, pwd, echo, pinfo
- Job control: jobs, kjob, overkill, fg
- I/O redirection and piping
- Background process management
- Signal handling
- Command history

## File Structure

- `shell.h` - Main header file with global variables and function declarations
- `shell.c` - Main implementation with shell loop and command execution
- `builtins.h/c` - Built-in command implementations (echo, cd, pwd, pinfo)
- `jobs.h/c` - Job control functionality
- `parsing.h/c` - Command parsing and tokenization

## Building the Shell

```bash
make
```

This will compile all the necessary files and create the executable `my_shell`.

## Running the Shell

```bash
./my_shell
```

## Available Commands

- `cd [dir]` - Change directory
- `pwd` - Print working directory
- `echo [text]` - Display text
- `pinfo [pid]` - Process information
- `jobs` - List background jobs
- `kjob [job_id] [signal]` - Send signal to job
- `fg [job_id]` - Bring job to foreground
- `overkill` - Kill all background processes
- `quit` - Exit the shell
- `newshell` - Open another shell instance

## I/O Redirection

The shell supports input and output redirection using `<` and `>` operators.

Example:

```
ls > output.txt
cat < input.txt
```

## Piping

The shell supports command piping using the `|` operator.

Example:

```
ls | grep .txt
```

## Background Processes

Add `&` at the end of a command to run it in the background.

Example:

```
sleep 10 &
```
