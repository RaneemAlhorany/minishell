#ifndef EXECUTION_H
#define EXECUTION_H

#include "./builtins/builtin.h"

typedef enum e_builtin_type
{
    BUILTIN_NONE,
    BUILTIN_ECHO,
    BUILTIN_CD,
    BUILTIN_PWD,
    BUILTIN_EXPORT,
    BUILTIN_UNSET,
    BUILTIN_ENV,
    BUILTIN_EXIT
} t_builtin_type;

typedef struct s_shell t_shell;
typedef struct s_cmd t_cmd;


int execute_ast(t_ast *node , t_shell *shell);
int execute_command_node (t_ast *node , t_shell *shell);
int execute_builtin(t_cmd *cmd, t_shell *shell, t_builtin_type type);
t_builtin_type get_builtin_type(char *cmd);

#endif