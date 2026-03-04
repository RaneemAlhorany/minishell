#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
    t_shell    shell;
    char       *input;

    (void)argc;
    (void)argv;

    shell = init_shell(envp);
    if (!shell.env)
        return (1);

    while (shell.is_running)
    {
        input = readline("minishell$ ");

        /* Ctrl + D */
        if (!input)
        {
            printf("exit\n");
            break;
        }

        /* Empty input */
        if (*input == '\0')
        {
            free(input);
            continue;
        }

        add_history(input);

        /* لاحقًا:
           - parsing
           - execution
        */

        free(input);
    }

    free_env_list(shell.env);
    return (shell.last_exit_status);
}



