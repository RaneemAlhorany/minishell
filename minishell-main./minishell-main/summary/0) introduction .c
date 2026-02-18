//! Minishell – Conceptual Understanding (Program-Level)

/*
//────────────────────────────────────────────────────────
! 1) What is Minishell?
//────────────────────────────────────────────────────────
? Minishell is an interactive command-line interpreter.
# It continuously takes user input, interprets it, executes it,
  and then returns to the prompt.
* It is NOT a full shell like bash, zsh, or fish.
* It is a simplified shell implemented strictly according to the subject.
^ Its goal is to understand how a shell works internally.

//────────────────────────────────────────────────────────
! 2) Program Life Cycle (Main Loop)
//────────────────────────────────────────────────────────
~ Conceptual flow (NOT real code):

while (true)
{
    display prompt
    read input (readline)
    if input == NULL → exit shell (Ctrl-D)
    tokenize input
    parse tokens into commands
    execute commands
    cleanup allocated resources
}

//────────────────────────────────────────────────────────
! 3) User Input
//────────────────────────────────────────────────────────
? Input is read using the readline library.

* Examples:
    ls -la
    echo "hello $USER"
    cat < infile | grep hi > outfile

//────────────────────────────────────────────────────────
! 4) Tokenization vs Parsing
//────────────────────────────────────────────────────────
? Tokenization:
# Splits raw input into meaningful tokens.

Example:
    input   : ls -la
    tokens  : [ls, -la]

? Parsing:
# Converts tokens into structured commands ready for execution.

Example:
    tokens   : [ls, -la]
    command  : name = ls
               args = [-la]

//────────────────────────────────────────────────────────
! 5) Required Features in Minishell
//────────────────────────────────────────────────────────
~ The project requires implementing:
    $ 1) Quotes handling (single and double)
    $ 2) Environment variable expansion
    $ 3) Redirections (<, >, >>, <<)
    $ 4) Pipes (|)
    $ 5) Built-in commands
    $ 6) Signal handling

//────────────────────────────────────────────────────────
! 6) Hardest Part of the Project
//────────────────────────────────────────────────────────
? Parsing quotes and environment variables.

Example:
    echo "hello $USER"  → expands $USER
    echo 'hello $USER'  → does NOT expand

^ Each '$' must be interpreted depending on context.

//────────────────────────────────────────────────────────
! 7) Builtins vs execve
//────────────────────────────────────────────────────────
? Built-in commands:
# Implemented directly inside the shell.

Examples:
    cd, echo, export, unset, pwd, env, exit

^ Some builtins MUST be executed in the parent process
  (e.g., cd, exit).

? External commands:
# Executed using execve.

Examples:
    ls, grep, cat

//────────────────────────────────────────────────────────
! 8) Pipes (Pipex as a Black Box)
//────────────────────────────────────────────────────────
? Pipe functionality will reuse the pipex mindset.
# We reuse the logic and mental model, not copy the project.
* fork, pipe, dup2, close remain the foundation.

//────────────────────────────────────────────────────────
! 9) Signals
//────────────────────────────────────────────────────────
! Signal handling is critical for evaluation.

Required behavior:
    ctrl + C → SIGINT  → new line + new prompt
    ctrl + \ → SIGQUIT → does nothing
    ctrl + D → EOF     → exit the shell

^ Only ONE global variable is allowed, storing the signal number.
^ Signal handlers must NOT access shell data structures.

────────────────────────────────────────────────────────
*/
