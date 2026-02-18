//! Minishell Architecture & Data Structures
//! Design Before Code

/*
////────────────────────────────────────────────────────────
//! 1) Global Architecture (Pipeline of Execution)
////────────────────────────────────────────────────────────
~ The minishell is implemented as a sequence of well-defined stages:

    $ 1. Read Input
    $ 2. Tokenization (Lexical Analysis)
    $ 3. Parsing (Structural Analysis)
    $ 4. Execution
    $ 5. Cleanup

!  Each stage:
     * Has a single responsibility
     * Uses its own data structures
     * Does NOT modify other stages' logic
*/

////────────────────────────────────────────────────────────
//! 2) Modules Overview
////────────────────────────────────────────────────────────
/*
~ 1. Input Module
   $ Responsibility: Read user input and manage history
   ! Function:
        char *read_input(void);
   ? Data:
        char *raw_input;

~ 2. Lexer Module
   $ Responsibility: Convert input string into tokens
   ! Function:
        t_token *lexer(char *input);
   ? Output:
        Linked list of tokens

~ 3. Parser Module
   $ Responsibility: Convert tokens into executable commands
   ! Function:
        t_cmd *parser(t_token *tokens);
   ? Output:
        Linked list of commands (pipeline-aware)

~ 4. Executor Module
   $ Responsibility: Execute commands (builtins or execve)
   ! Function:
        int execute(t_cmd *cmds, char **envp);

~ 5. Builtins Module
   $ Responsibility: Handle shell built-in commands
   ! Function:
        int exec_builtin(t_cmd *cmd, t_env *env);

~ 6. Redirections Module
   $ Responsibility: Handle < > >> << redirections
   ! Function:
        int handle_redirections(t_cmd *cmd);

~ 7. Pipes Module
   $ Responsibility: Handle pipelines using pipe/fork/dup2
   ! Function:
        int handle_pipes(t_cmd *cmds);

~ 8. Signals Module
   $ Responsibility: Handle SIGINT, SIGQUIT
   ! Function:
        void setup_signals(void);

~ 9. Environment Module
   $ Responsibility: Manage and expand environment variables
   ! Function:
        char *expand_env(char *input, t_env *env);

~ 10. Utils Module
   $ Responsibility: Helper utilities (libft-based)
   ! Function:
        Various helpers

~ 11. Cleanup Module
   $ Responsibility: Free all allocated memory safely
   ! Function:
        void cleanup(t_token *tokens, t_cmd *cmds);
*/

////────────────────────────────────────────────────────────
//! 3) Core Data Structures
////────────────────────────────────────────────────────────
/*
Token structure represents the smallest lexical unit.
*/

typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,        // <
    TOKEN_REDIR_OUT,       // >
    TOKEN_REDIR_APPEND,    // >>
    TOKEN_HEREDOC          // <<
}   t_token_type;

typedef struct s_token
{
    t_token_type    type;
    char            *value;
    struct s_token  *next;
}   t_token;

/*
Command structure represents a single executable command.
*/

typedef struct s_cmd
{
    char            *cmd;        // command name
    char            **args;      // argv-style arguments
    int             infile;      // input fd
    int             outfile;     // output fd
    int             is_builtin;
    struct s_cmd    *next;       // next command in pipeline
}   t_cmd;

////────────────────────────────────────────────────────────
//! 4) Data Flow Summary
////────────────────────────────────────────────────────────
/*
    char *input
        ↓
    t_token *tokens
        ↓
    t_cmd *cmds
        ↓
    execution
*/
