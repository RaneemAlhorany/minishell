*This project has been created as part of the 42 curriculum by babo-sai , ralhoura.*

## Description

minishell is a small Unix-like shell written in C as part of the 42 curriculum. Its goal is to reproduce the core behavior of a command interpreter: reading user input, tokenizing and parsing commands, expanding variables, handling redirections and heredocs, executing pipelines, and providing the standard shell builtins.

This project is structured into dedicated modules for lexing, parsing, expansion, environment management, signal handling, and command execution. It supports interactive use through GNU Readline and is designed to behave like a simplified Bash-compatible shell.

## Instructions

### Requirements

- A C compiler such as `cc`
- `make`
- GNU Readline development libraries
- A Linux environment

### Compilation

```bash
make
```

This builds the `minishell` executable at the repository root.

### Useful targets

```bash
make clean
make fclean
make re
```

### Execution

```bash
./minishell
```

Once launched, the shell opens an interactive prompt where you can type commands, use pipes, redirections, heredocs, environment variables, and builtins such as `cd`, `echo`, `env`, `export`, `pwd`, `unset`, and `exit`.

## Features

- Interactive command prompt with history support
- Lexer and parser for shell syntax
- Environment variable handling and expansion
- Pipes, input/output redirections, append redirections, and heredocs
- Wildcard expansion
- Builtins: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, and `unset`
- Signal handling for interactive shell behavior

## Project Structure

### Root Files

- [main.c](main.c): program entry point; initializes the shell, installs signal handlers, starts the interactive loop, and performs cleanup on exit.
- [Makefile](Makefile): builds the executable, compiles Libft, and provides clean/rebuild/test targets.
- [minishell.h](minishell.h): central header that gathers shared includes, enums, structs, and project-wide declarations.

### env

- [env/env.h](env/env.h): environment module declarations and related types.
- [env/env.c](env/env.c): core environment initialization and management.
- [env/env_list.c](env/env_list.c): linked-list handling for environment variables.
- [env/env_helper.c](env/env_helper.c): helper utilities for environment lookup and updates.
- [env/get_env_value.c](env/get_env_value.c): retrieves the value of a named environment variable.

### lexer

- [lexer/lexer.h](lexer/lexer.h): lexer declarations, token-related types, and prototypes.
- [lexer/lexer.c](lexer/lexer.c): converts raw input into tokens.
- [lexer/lexer_utils.c](lexer/lexer_utils.c): low-level helpers for character classification and token scanning.
- [lexer/lexer_helper.c](lexer/lexer_helper.c): additional lexer helpers for splitting and special cases.
- [lexer/token.c](lexer/token.c): token creation, linking, and cleanup helpers.

### expansion

- [expansion/expand.h](expansion/expand.h): expansion module declarations.
- [expansion/expand.c](expansion/expand.c): main expansion logic for variables and shell values.
- [expansion/utils_expand.c](expansion/utils_expand.c): helpers used during expansion.
- [expansion/utils_expand_buffer.c](expansion/utils_expand_buffer.c): buffer management used while building expanded strings.

### parser

- [parser/parsing.h](parser/parsing.h): parsing declarations, AST definitions, and parser prototypes.
- [parser/parser.c](parser/parser.c): main parser entry point that builds the command structure.
- [parser/build_command_1.c](parser/build_command_1.c): first stage of command construction from tokens.
- [parser/build_command_2.c](parser/build_command_2.c): continuation of command construction logic.
- [parser/build_command_3.c](parser/build_command_3.c): additional command-building helpers and AST wiring.
- [parser/parser_helper.c](parser/parser_helper.c): helper utilities used by the parser.
- [parser/shared_method.c](parser/shared_method.c): functions shared by multiple parser stages.
- [parser/syntax_check_lexer_1.c](parser/syntax_check_lexer_1.c): initial syntax validation for token streams.
- [parser/syntax_check_lexer_2.c](parser/syntax_check_lexer_2.c): additional syntax validation and edge-case handling.

### signals

- [signals/signals.h](signals/signals.h): signal-related declarations.
- [signals/signals.c](signals/signals.c): signal setup and runtime handling.
- [signals/signals_utils.c](signals/signals_utils.c): helper functions for signal behavior.

### shell

- [shell/shell.h](shell/shell.h): shell state declarations and helper prototypes.
- [shell/shell.c](shell/shell.c): shell initialization and top-level state creation.
- [shell/shell_execution.c](shell/shell_execution.c): interactive shell execution flow.
- [shell/shlvl.c](shell/shlvl.c): updates the `SHLVL` environment variable.
- [shell/helper_1.c](shell/helper_1.c): general shell helpers.
- [shell/helper_2.c](shell/helper_2.c): additional shell helpers.
- [shell/shell_free_1.c](shell/shell_free_1.c): first stage of shell resource cleanup.
- [shell/shell_free_2.c](shell/shell_free_2.c): additional cleanup helpers.
- [shell/shell_helper.c](shell/shell_helper.c): shared shell utility functions.

### execution

- [execution/execution.h](execution/execution.h): execution module declarations.
- [execution/execute_ast.c](execution/execute_ast.c): runs the AST after parsing.
- [execution/execute_builtin.c](execution/execute_builtin.c): detects and executes builtins.
- [execution/execute_command_1.c](execution/execute_command_1.c): first stage of command execution.
- [execution/execute_command_2.c](execution/execute_command_2.c): continuation of command execution logic.
- [execution/execute_external_1.c](execution/execute_external_1.c): prepares execution of external commands.
- [execution/execute_external_2.c](execution/execute_external_2.c): process creation and execution helpers.
- [execution/execute_external_3.c](execution/execute_external_3.c): additional external execution logic.
- [execution/execute_external_4.c](execution/execute_external_4.c): final external execution helpers.
- [execution/execute_pipe.c](execution/execute_pipe.c): pipe creation and execution flow.
- [execution/execute_pipe_helper.c](execution/execute_pipe_helper.c): helpers for pipe execution.
- [execution/redirections.c](execution/redirections.c): applies redirections to file descriptors.
- [execution/redirections_helper.c](execution/redirections_helper.c): helper utilities for redirection setup.
- [execution/heardoc.c](execution/heardoc.c): heredoc execution and input collection.
- [execution/heardoc_helper_1.c](execution/heardoc_helper_1.c): first heredoc helper stage.
- [execution/heardoc_helper_2.c](execution/heardoc_helper_2.c): additional heredoc helpers.
- [execution/special_char.c](execution/special_char.c): handling for shell special characters during execution.
- [execution/shared_method.c](execution/shared_method.c): functions shared across execution submodules.
- [execution/wildcard_1.c](execution/wildcard_1.c): first stage of wildcard expansion.
- [execution/wildcard_2.c](execution/wildcard_2.c): second stage of wildcard expansion.
- [execution/wildcard_3.c](execution/wildcard_3.c): third stage of wildcard expansion.
- [execution/wildcard_4.c](execution/wildcard_4.c): fourth stage of wildcard expansion.
- [execution/wildcard_5.c](execution/wildcard_5.c): fifth stage of wildcard expansion.

### execution/builtins

- [execution/builtins/builtin.h](execution/builtins/builtin.h): builtin declarations and shared builtin types.
- [execution/builtins/builtin_cd.c](execution/builtins/builtin_cd.c): implementation of `cd`.
- [execution/builtins/builtin_cd_helper.c](execution/builtins/builtin_cd_helper.c): helpers for `cd`.
- [execution/builtins/builtin_echo.c](execution/builtins/builtin_echo.c): implementation of `echo`.
- [execution/builtins/builtin_echo_helper.c](execution/builtins/builtin_echo_helper.c): helpers for `echo`.
- [execution/builtins/builtin_env.c](execution/builtins/builtin_env.c): implementation of `env`.
- [execution/builtins/builtin_env_helper.c](execution/builtins/builtin_env_helper.c): helpers for `env`.
- [execution/builtins/builtin_exit.c](execution/builtins/builtin_exit.c): implementation of `exit`.
- [execution/builtins/builtin_exit_helper.c](execution/builtins/builtin_exit_helper.c): helpers for `exit`.
- [execution/builtins/builtin_export.c](execution/builtins/builtin_export.c): implementation of `export`.
- [execution/builtins/builtin_export_handle1.c](execution/builtins/builtin_export_handle1.c): first part of `export` handling.
- [execution/builtins/builtin_export_handle2.c](execution/builtins/builtin_export_handle2.c): second part of `export` handling.
- [execution/builtins/builtin_export_options.c](execution/builtins/builtin_export_options.c): validation and options support for `export`.
- [execution/builtins/builtin_export_print.c](execution/builtins/builtin_export_print.c): formatted printing for exported variables.
- [execution/builtins/builtin_pwd.c](execution/builtins/builtin_pwd.c): implementation of `pwd`.
- [execution/builtins/builtin_unset.c](execution/builtins/builtin_unset.c): implementation of `unset`.
- [execution/builtins/builtin_unset_helper.c](execution/builtins/builtin_unset_helper.c): helpers for `unset`.
- [execution/builtins/shared_method.c](execution/builtins/shared_method.c): shared builtin helper functions.


## Builtins and added options

This project implements the common shell builtins and supports several options and behaviors worth noting. The implementations live in the `execution/builtins` folder.

- `pwd`: supports `-L` and `-P`.
  - `-L`: print the `PWD` value from the environment when available (default behavior).
  - `-P`: print the actual current working directory (uses `getcwd`) and ignore the `PWD` environment value.

- `env`: supports options for running a command with a modified environment.
  - `-i`: run the command with an empty environment (clears inherited variables for the new environment).
  - `-u NAME` or `-uNAME`: remove `NAME` from the environment for the temporary environment.
  - `--`: end of options.
  - The builtin also supports temporary assignments before a command, e.g. `VAR=value command` or `env VAR=value command` — the assignment is visible only to the command and is removed afterwards (temporary env behavior).

- `export`: supports printing and special handling options.
  - `-p`: print exported variables in a formatted way.
  - `-n`: handle `-n` behavior when updating variables (see implementation in `builtin_export_options.c`).
  - Usage: `export [-fn] [name[=value] ...]` or `export -p`.

- `echo`: supports `-n`, `-e`, `-E`.
  - `-n`: suppress trailing newline.
  - `-e`: enable backslash escape interpretation.
  - `-E`: disable backslash escape interpretation.

- `unset`: supports the `-v` option (`unset -v NAME`).

- `cd`: supports `--help` and behaves like the standard `cd` with special handling for `-` (go to `OLDPWD`), `~` (HOME), and respects `CDPATH`. The help text mentions `-L` / `-P` behavior as well.

- `exit`: exits the shell; accepts an optional numeric exit code.

If you want, I can add a short examples subsection with common usage patterns (temporary env assignment, `env -i`, `pwd -P`, `echo -n`, etc.) — should I add that now?


## Minishell Comprehensive Test Suite

## Running Checks

### Valgrind

```bash
valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell
```

### Zombie Processes

```bash
ps aux | grep Z
```

Expected: no zombie processes.

## Basic Behavior

### Empty Input
- Input: press Enter
- Output: new prompt
- Exit: `0`

### Spaces / Tabs
- Input: spaces or tabs only
- Output: new prompt
- Exit: `0`

## Command Execution

- `/bin/ls`
  - Expected: list current directory
  - Exit: `0`
- `/bin/ls filethatdoesntexist`
  - Expected: error
  - Exit: non-zero
- `ls`
  - Expected: works with `PATH`
  - Exit: `0`
- `unset PATH; ls`
  - Expected: command not found
  - Exit: `127`
- `PATH=/bin:/usr/bin; ls`
  - Expected: command works again
  - Exit: `0`
- `./a.out`
  - Expected: executes relative binary
  - Exit: `0`
- Random text like `abcd123`
  - Expected: command not found
  - Exit: `127`
- Very long command
  - Expected: no crash
  - Exit: `0` or error depending on limits

## Echo

- `echo hello`
  - Expected: `hello`
  - Exit: `0`
- `echo -n hello`
  - Expected: `hello` without newline
  - Exit: `0`
- `echo '$USER'`
  - Expected: `$USER`
  - Exit: `0`
- `echo "$USER"`
  - Expected: expanded user value
  - Exit: `0`
- `echo $USER`
  - Expected: expanded value
  - Exit: `0`
- `echo "$PWD""$USER"'$HOME'`
  - Expected: concatenated expansion with single-quoted literal part
  - Exit: `0`
- `echo ss # test`
  - Expected: `ss`
  - Exit: `0`
- `echo -nnnnnnnn --n -nnnnnnnnb test`
  - Expected: option parsing behavior for `-n`
  - Exit: `0`

## Redirections

- `cat < minishell.h > out.txt`
  - Expected: file content copied to `out.txt`
  - Exit: `0`
- `echo hello >> out.txt`
  - Expected: append `hello`
  - Exit: `0`
- `cat << EOF`
  - Expected: heredoc until `EOF`
  - Exit: `0`
- `ls >`
  - Expected: syntax error near unexpected token `newline`
  - Exit: `2`
- `>`
  - Expected: syntax error near unexpected token `newline`
  - Exit: `2`
- `>>`
  - Expected: syntax error near unexpected token `newline`
  - Exit: `2`
- `>>>`
  - Expected: syntax error near unexpected token `>`
  - Exit: `2`
- `>>>>` and longer
  - Expected: syntax error near unexpected token `>>`
  - Exit: `2`
- `<`
  - Expected: syntax error near unexpected token `newline`
  - Exit: `2`
- `<<`
  - Expected: syntax error near unexpected token `newline`
  - Exit: `2`
- `<<<`
  - Expected: syntax error near unexpected token `newline`
  - Exit: `2`
- `<<<<`
  - Expected: syntax error near unexpected token `<`
  - Exit: `2`
- `<<<<<`
  - Expected: syntax error near unexpected token `<<`
  - Exit: `2`
- `<<<<<<` and longer
  - Expected: syntax error near unexpected token `<<<`
  - Exit: `2`
- `cat << EOF + input + EOF`
  - Expected: heredoc content displayed
  - Exit: `0`
- `cat << 1 >`
  - Expected: heredoc then syntax error
  - Exit: `2`
- `export test="123 test"; < $test`
  - Expected: ambiguous redirect
  - Exit: `1`
- `export test="123 test"; ls > $test`
  - Expected: ambiguous redirect
  - Exit: `1`
- `> /`
  - Expected: `/: Is a directory`
  - Exit: non-zero
- `<< 123 the CTRL+C`
  - Expected: heredoc interrupted by Ctrl+C
  - Exit: `130`
- `<< 123 cat` with EOF interruption
  - Expected: heredoc warning / partial input handling
  - Exit: `0`

## Pipes

- `cat | cat | echo`
  - Expected: empty output from final `echo`
  - Exit: `0`
- `pwd | (ls $$ cat ) | echo hi`
  - Expected: `hi`
  - Exit: `0`
- `echo hi || pwd | ( (ls $$ cat ) | echo hi)`
  - Expected: `hi`
  - Exit: `0`
- `yes yes | head -n 10000000 | wc`
  - Expected: wc output for the pipeline
  - Exit: `0`
- `cat | cat | cat | echo`
  - Expected: empty output
  - Exit: `0`
- `exit 1 | exit 2 | exit 3`
  - Expected: nothing printed
  - Exit: `3`
- `cat Makefile | base64 | xxd -p | xxd -r -p | base64 --decode`
  - Expected: original Makefile content
  - Exit: `0`
- `cat Makefile | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e`
  - Expected: Makefile with `$` end markers
  - Exit: `0`
- `echo | echo | echo | echo | echo | echo | echo | echo | echo | echo | echo | echo | echo`
  - Expected: empty output
  - Exit: `0`
- `.|..|.`
  - Expected: dot and dot-dot error handling
  - Exit: `2`
- `sleep 1000 | ls | sleep 1000`
  - Expected: pipeline and signal handling behavior
  - Exit: `130` on Ctrl+C, `131` on Ctrl+\\
- `sleep 25 | ls | sleep 1000` or `sleep 1000 | ls | sleep 25`
  - Expected: background pipeline visible in `ps aux`, no zombies
  - Exit: `0`
- `test && echo hi | sleep 10 || echo nice`
  - Expected: logical operators with pipeline
  - Exit: `0`
- `test && exit || yes yes | head -n 100 && cat`
  - Expected: pipeline with control operators
  - Exit: `0` or signal-dependent
- `test || exit && echo hi`
  - Expected: exit before `hi`
  - Exit: `1`
- `(ls && pwd && ls -la)`
  - Expected: grouped execution
  - Exit: `0`
- `echo .*`
  - Expected: hidden-file glob expansion
  - Exit: `0`
- `echo *`
  - Expected: non-hidden glob expansion
  - Exit: `0`
- `echo .*.`
  - Expected: pattern expansion result
  - Exit: `0`

## Environment Variables

- `env`
  - Expected: environment listing
  - Exit: `0`
- `export VAR=value`
  - Expected: variable exported
  - Exit: `0`
- `unset VAR`
  - Expected: variable removed
  - Exit: `0`
- `echo $non_exist`
  - Expected: empty output
  - Exit: `0`
- `echo $SHELL`
  - Expected: shell path
  - Exit: `0`
- `$SHELL`
  - Expected: execute shell from variable if supported
  - Exit: `0`
- `echo $? + $?`
  - Expected: expansion of last status values
  - Exit: `0`
- `echo $0$1230$0`
  - Expected: invalid variable handling behavior
  - Exit: `0`
- `echo $PATH$PATH$PATH$PATH$PATH$PATH$PATH$PATH...`
  - Expected: concatenated expansion
  - Exit: `0`

## SHLVL and Special Vars

- `echo $SHLVL` then run `./minishell` then `echo $SHLVL`
  - Expected: shell level increments in child shell
  - Exit: `0`
- `export SHLVL=999` then `./minishell`
  - Expected: SHLVL resets to `1` in new shell
  - Exit: `0`
- `export SHLVL=-129139` then `./minishell`
  - Expected: SHLVL becomes `0`
  - Exit: `0`
- `ls -la` then `echo $_`
  - Expected: last argument of previous command
  - Exit: `0`

## Export

- `export test1="abcd" test2="1234" test3="   " test4`
  - Expected: variables exported, empty/unset handling
  - Exit: `0`
- `export 1test="al"`
  - Expected: invalid identifier
  - Exit: `1`
- `export test="123" 1test="est" test3="abcd"`
  - Expected: invalid identifier for `1test`
  - Exit: `1`
- `export test_empty`
  - Expected: visible in `export`, empty value
  - Exit: `0`

## Unset

- `unset USER`
  - Expected: `USER` removed
  - Exit: `0`
- `unset USER PATH`
  - Expected: both removed
  - Exit: `0`

## Builtins

### cd
- `cd not_exist_directory`
  - Expected: no such file or directory
  - Exit: `1`
- `cd /dev/vboxusb`
  - Expected: permission denied
  - Exit: `1`
- `cd ../../`
  - Expected: move to grandparent directory
  - Exit: `0`
- `cd a b`
  - Expected: too many arguments
  - Exit: `1`
- `cd -`
  - Expected: previous directory
  - Exit: `0`
- `cd ..`
  - Expected: parent directory
  - Exit: `0`

### pwd
- `pwd`
  - Expected: current working directory
  - Exit: `0`

### exit
- `exit`
  - Expected: exit with status `0`
- `exit 42`
  - Expected: exit with status `42`
- `exit -1`
  - Expected: exit with status `255`
- `exit 9223372036854775808-`
  - Expected: numeric argument required
  - Exit: `2`
- `exit -9223372036854775808`
  - Expected: exit normally
  - Exit: `0`
- `exit 9223372036854775808`
  - Expected: numeric argument required
  - Exit: `2`
- `exit 9223372036854775807`
  - Expected: exit with normalized status behavior
  - Exit: `255`
- `exit 1 abcd`
  - Expected: too many arguments
  - Exit: `1`
- `exit 23 abcd`
  - Expected: too many arguments
  - Exit: `1`
- `exit abcd`
  - Expected: numeric argument required
  - Exit: `2`
- `exit abc 123`
  - Expected: numeric argument required
  - Exit: `2`

## Syntax Errors

- `ls >`
- `>`
- `>>`
- `ls <<<<<<<<<<<< t.txt`
  - Expected: syntax error near unexpected token `<<<`
  - Exit: `2`
- `ls >>>>>>>>> t.txt`
  - Expected: syntax error near unexpected token `>>`
  - Exit: `2`
- `|`
- `||`

Exit: `2`

## Signals

- Ctrl+C at empty prompt
  - Expected: new prompt
  - Exit: `130`
- Ctrl+\\ at empty prompt
  - Expected: ignored / last status stays
- Ctrl+D at empty prompt
  - Expected: shell exits
  - Exit: `0`
- Ctrl+C in heredoc
  - Expected: heredoc interrupted
  - Exit: `130`
- Ctrl+C in pipeline
  - Expected: foreground children terminated
  - Exit: `130`
- Ctrl+\\ in pipeline
  - Expected: terminate with signal-related status
  - Exit: `131`

## Error Handling

- `./`
  - Expected: is a directory
  - Exit: `126`
- `.`
  - Expected: filename argument required / usage
  - Exit: `2`
- `/`
  - Expected: is a directory
  - Exit: `126`
- `file/`
  - Expected: no such file or directory
  - Exit: `127`
- executable file test with `touch file_test; chmod +x file_test; ./file_test`
  - Expected: runs without output
  - Exit: `0`
- `***************a******k*****`
  - Expected: command not found
  - Exit: `127`

## Heredoc

- `cat << ls > out | cat << ls`
  - Expected: each heredoc processed, last input used for corresponding command
  - Exit: `0`
- `ls <<1 | cat -e | cat -e | cat -e > o1 | cat <<1 | wc -l > o2 | cat <o2 >old2 | pwd | cat -e >o2`
  - Expected: complex heredoc + pipe + redirection flow
  - Exit: `0`
- `ls <<1 | <<1 cat -e > o1 | cat <<1 | cat >o1`
  - Expected: repeated heredoc race check case
  - Exit: `0`
- `ls <<1 | cat -e > o1 | cat | cat >o1`
  - Expected: heredoc and pipe handling
  - Exit: `0`
- `cat << 123 cat`
  - Expected: heredoc until EOF / warning behavior
  - Exit: `0`
- `cat << 123 + Ctrl+D`
  - Expected: heredoc ends on EOF
  - Exit: `0`
- `<< 123 cat << 234 -e > out`
  - Expected: last heredoc content used, output written to file
  - Exit: `0`

## Custom and Complex Cases

- `export test="   "` then `echo $test $test  $test abcd`
  - Expected: spaces collapse in unquoted expansions
  - Exit: `0`
- `export test="   "` then `echo $non_existent_variable $test  $test`
  - Expected: empty output
  - Exit: `0`
- `export test="   "` then `echo $test  123 $test`
  - Expected: command not found for `123`
  - Exit: `127`
- `export test="   abcd   123 "` then `echo $test  "$test"`
  - Expected: mixed quoted/unquoted spacing behavior
  - Exit: `0`
- `export test="ls        -la"` then `$test`
  - Expected: command runs with spaces normalized
  - Exit: `0`
- `export test="ls        -la"` then `"$test"`
  - Expected: command not found
  - Exit: `127`
- `export test="ls        -la"` then `'$test'`
  - Expected: command not found
  - Exit: `127`
- `echo $test` with `test="123 test"` used in redirects
  - Expected: ambiguous redirect behavior
  - Exit: `1`

## Bonus / Optional

- `echo -nnnnnnn -n -nnnennE test`
  - Expected: optional behavior only
  - Exit: `0`
- `echo -nnnnnnnn -nnnnerEEEE test`
  - Expected: optional behavior only
  - Exit: `0`
- `echo test`
  - Expected: literal output and option parsing edge-case behavior
  - Exit: `0`

## Evaluation Checklist

### Core Features
- Prompt displays correctly
- Commands execute correctly: absolute, relative, and PATH-based
- Pipes work properly
- Redirections work: `>`, `>>`, `<`, `<<`
- Heredoc behaves like bash
- Environment variables expand correctly
- Quotes are handled correctly

### Builtins
- `echo` including `-n`
- `cd` all cases
- `pwd`
- `export`
- `unset`
- `env`
- `exit` edge cases

### Expansion
- `$VAR` expands
- `$?` works
- Quotes affect expansion correctly
- Invalid variables handled

### Pipes and Processes
- Multiple pipes work
- No zombie processes
- Correct exit status of last command

### Signals
- Ctrl+C behaves correctly
- Ctrl+\\ ignored properly
- Ctrl+D exits shell
- Signals handled inside pipelines

### Errors
- Syntax errors detected
- Command not found -> `127`
- Permission denied -> `126`
- No crashes on invalid input

### Memory
- No leaks in Valgrind
- No file descriptor leaks

### Edge Cases
- Empty input
- Only spaces/tabs
- Very long commands
- Complex combinations of pipes and redirections


## Project Statistics

- **Total Lines of Code**: 8,989
- **Total Functions**: 301
- **Total Files**: 115


## Resources

Classic references used while building this project:

- mossajehad notion: https://mossajehad.notion.site/Minishell-25a500f820cf8042bad6c58a48e1b841
- POSIX Shell Command Language: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html
- Readline documentation: https://tiswww.case.edu/php/chet/readline/rltop.html
- BASH : https://www.gnu.org/software/bash/

- 42 minishell subject and internal notes from the curriculum

AI  was used to help us understand certain aspects and improve the system, and to gather ideas for simplifying the process. The rest of the code was written, developed, and reviewed by us.
