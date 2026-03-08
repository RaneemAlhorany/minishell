#include "execution.h"

int execute_builtin(t_cmd *cmd, t_shell *shell, t_builtin_type type)
{
    if (!cmd || !shell)
        return (0);

    if (type == BUILTIN_ECHO)
        return builtin_echo(cmd, shell);
    else if (type == BUILTIN_CD)
         return builtin_cd(cmd, shell);
    else if (type == BUILTIN_PWD)
        return builtin_pwd(cmd, shell);
    else if (type == BUILTIN_EXPORT)
        return builtin_export(cmd, shell);
    else if (type == BUILTIN_UNSET)
        return builtin_unset(cmd, shell);
    else if (type == BUILTIN_ENV)
        return builtin_env(cmd, shell);
    else if (type == BUILTIN_EXIT)
        return builtin_exit(cmd, shell);
    return (0);
}




t_builtin_type get_builtin_type(char *cmd)
{
    if (!cmd)
        return BUILTIN_NONE;
    if (strcmp(cmd, "echo") == 0)
        return BUILTIN_ECHO;
    else if (strcmp(cmd, "cd") == 0)
        return BUILTIN_CD;
    else if (strcmp(cmd, "pwd") == 0)
        return BUILTIN_PWD;
    else if (strcmp(cmd, "export") == 0)
        return BUILTIN_EXPORT;
    else if (strcmp(cmd, "unset") == 0)
        return BUILTIN_UNSET;
    else if (strcmp(cmd, "env") == 0)
        return BUILTIN_ENV;
    else if (strcmp(cmd, "exit") == 0)
        return BUILTIN_EXIT;
    else
        return BUILTIN_NONE;
}




