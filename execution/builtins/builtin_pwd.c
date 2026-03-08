
// edit +test

#include "builtin.h"

// to make it same signature 
// + dont broken function pointer

int builtin_pwd(t_cmd *cmd, t_shell *shell)
{
    char *cwd;

    (void)cmd;
    (void)shell;
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("pwd");
        return (1);
    }
    ft_putendl_fd(cwd , 1);
    free(cwd);
    return (0);
}



