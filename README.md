# Minishell

A simplified shell implementation inspired by bash, developed as part of the 42 core curriculum.

## Summary

Minishell is a challenging project that implements a basic shell similar to bash. It focuses on process creation and control, file descriptor manipulation, and signal handling. This project demonstrates our understanding of Unix system calls, environment variables, and shell functionality.

The implementation features a robust parser that handles commands with arguments, redirections, pipes, and heredocs. We've built a complete command execution system that supports both built-in commands and external binaries. Special attention was given to handling environment variables, signal interrupts, and maintaining proper exit status codes.

This project required deep knowledge of C programming, Unix processes, and shell behavior. The code is structured in a modular way, with clear separation between lexical analysis (tokenization), syntactic analysis (parsing), and execution.

## Table of Contents

- [Minishell](#minishell)
	- [Summary](#summary)
	- [Table of Contents](#table-of-contents)
	- [Quick overview](#quick-overview)
	- [Features](#features)
	- [Building](#building)
	- [Architecture](#architecture)
		- [Tokenization](#tokenization)
		- [Parsing](#parsing)
		- [Abstract Syntax Tree](#abstract-syntax-tree)
		- [Execution](#execution)
	- [Usage Examples](#usage-examples)
		- [Basic Commands](#basic-commands)
		- [Redirections](#redirections)
		- [Pipes](#pipes)
		- [Heredoc](#heredoc)
	- [Builtins](#builtins)
		- [echo](#echo)
		- [cd](#cd)
		- [pwd](#pwd)
		- [export](#export)
		- [unset](#unset)
		- [env](#env)
		- [exit](#exit)
	- [Exit Status](#exit-status)
	- [Signal Handling](#signal-handling)
	- [Authors](#authors)

## Quick overview

Minishell is a simple command-line interpreter that replicates core functionalities of bash. It provides command execution, environment variable management, pipes, redirections, and various shell builtins.

## Features

- Command execution from (`$PATH`) and absolute/relative paths
- Environment variable expansion (`$VAR`)
- Exit status expansion (`$?`)
- Input/output redirections (`>`, `<`, `>>`)
- Heredoc (`<<`)
- Pipes (`|`)
- Signal handling (`Ctrl`+`C`, `Ctrl`+`D`, `Ctrl`+`\`)
- Builtin commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit` implemented by us

## Building

Clone the repository and build the project:

```bash
git clone https://github.com/sknefi/Minishell.git

cd Minishell

make # build the project
```

Run the shell:

```bash
./minishell
```

For memory leak detection and detailed analysis, use the provided suppression file for readline:

```bash
valgrind --suppressions=readline.supp -s --leak-check=full ./minishell
```

This command will run Valgrind with readline-related leaks suppressed, showing a summary (-s) and performing full leak checking.

## Architecture

Minishell is built with a modular architecture consisting of several key components:

### Tokenization

The tokenization process in `src/token/token.c` breaks the input line into tokens. It handles:

1. Command names and arguments
2. Operators (`|`, `>`, `<`, `>>`, `<<`)
3. Environment variables
4. Quoted strings

Each token is assigned a type from the `t_token_types` enum and organized in a linked list for further processing.

Example:
```bash
echo "Hello $USER" | grep Hello > output.txt
```

Is tokenized as:
- `echo` (TOKEN_WORD)
- `"Hello $USER"` (TOKEN_WORD)
- `|` (TOKEN_PIPE)
- `grep` (TOKEN_WORD)
- `Hello` (TOKEN_WORD)
- `>` (TOKEN_REDIRECTION_OUT)
- `output.txt` (TOKEN_WORD)

### Parsing

The parser in `src/ast/ast.c` transforms the token list into an Abstract Syntax Tree (AST). It follows these steps:

1. Recognize command structures
2. Identify redirections and pipes
3. Create a hierarchical tree representing command relationships
4. Validate syntax

### Abstract Syntax Tree

The AST uses node types from the `t_node_types` enum:
- `NODE_CMD`: Command with arguments
- `NODE_PIPE`: Pipe operator
- `NODE_REDIRECTION_IN`, `NODE_REDIRECTION_OUT`, `NODE_APPEND`, `NODE_HEREDOC`: Redirection nodes

Each node contains:
- Type
- Data (command arguments or redirection filenames)
- Left and right child nodes

### Execution

The execution engine in `src/exec/sh_exec.c` traverses the AST and executes commands accordingly:

1. For `NODE_CMD`, it first tries to execute as a builtin, then as an external command
2. For `NODE_PIPE`, it creates a pipe and forks two processes
3. For redirection nodes, it sets up file descriptors and executes the command

## Usage Examples

### Basic Commands

```bash
# Simple command execution
ls -la

# Environment variable usage
echo $HOME

# Path handling
/bin/ls

# Exit status
echo $?
```

### Redirections

```bash
# Output redirection (create or overwrite)
echo Hello > file.txt

# Output redirection (append)
echo World >> file.txt

# Input redirection
cat < file.txt

# Multiple redirections
cat < input.txt > output.txt
```

### Pipes

```bash
# Simple pipe
ls -la | grep .c

# Multiple pipes
ls -la | grep .c | wc -l

# Pipe with redirections
ls -la | grep .c > output.txt
```

### Heredoc

```bash
# Basic heredoc
cat << EOF
This is a heredoc
It allows multiline input
EOF

# Heredoc with pipes and redirections
cat << EOF | grep hello > output.txt
hello world
goodbye world
EOF
```

## Builtins

### echo
Displays a line of text.
```bash
echo Hello World
echo -n Hello World  # No newline
echo -n -nn -nnnnnn Hello World # No newline
```

### cd
Changes the current directory.
```bash
cd /absolute/path/to/directory
cd relative/path/to/directory
cd ..  # Parent directory
cd -   # Previous directory
cd     # Home directory
cd ~   # Home directory
```

### pwd
Prints the current working directory.
```bash
pwd
```

### export
Sets environment variables.
```bash
export VAR=value
export VAR1=value1 VAR2=value2 # export multiple variables
export    # Sorted list of all exported variables
```

### unset
Removes environment variables.
```bash
unset VAR
unset VAR1 VAR2 # unset multiple variables
```

### env
Displays all environment variables.
```bash
env
```

### exit
Exits the shell with an optional status code.
```bash
exit
```

## Exit Status

The exit status of the last command is stored in the `$?` variable, following bash conventions:
- `0`: Success
- `1`: General error
- `127`: Command not found
- `130`: Terminated by Ctrl+C (SIGINT)
- `131`: Terminated by Ctrl+\ (SIGQUIT)
- Other values: Depends on the command and its exit status

## Signal Handling

Minishell handles the following signals:
- `Ctrl+C` (SIGINT): Interrupts the current command even in heredoc
- `Ctrl+D` (EOF): Exits the shell (sends EOF to readline)
- `Ctrl+\` (SIGQUIT): Ignored in interactive mode, terminates with core dump in child processes

The signal handling is implemented in `src/signal/signals_01.c` and `src/signal/signals_02.c`.

## Authors

This minishell project was built by:
- **Filip Karika**
- **Tym Mateja**

As part of the 42 School curriculum. 