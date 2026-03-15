#include "execution.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

char *join_path(const char *dir, const char *cmd)
{
    char *tmp;
    char *full;

    if (!dir || !cmd)
        return (NULL);
    tmp = ft_strjoin(dir, "/");
    if (!tmp)
        return (NULL);
    full = ft_strjoin(tmp, cmd);
    free(tmp);
    return (full);
}

char **env_list_to_envp(t_env *env)
{
    int        i;
    int        len;
    t_env      *cur;
    char       **envp;
    char       *line;

    len = 0;
    cur = env;
    while (cur)
    {
        len++;
        cur = cur->next;
    }
    envp = malloc(sizeof(char *) * (len + 1));
    if (!envp)
        return (NULL);
    i = 0;
    cur = env;
    while (cur)
    {
        line = ft_strjoin(cur->key, "=");
        if (!line)
            break;
        envp[i] = ft_strjoin(line, cur->value ? cur->value : "");
        free(line);
        if (!envp[i])
            break;
        i++;
        cur = cur->next;
    }
    if (i != len)
    {
        while (i--) 
            free(envp[i]);
        free(envp);
        return (NULL);
    }
    envp[i] = NULL;
    return (envp);
}

void free_envp(char **envp)
{
    int i;

    if (!envp)
        return;
    i = 0;
    while (envp[i])
        free(envp[i++]);
    free(envp);
}

char *find_program_on_path(char *name, t_shell *shell)
{
    char    *path;
    char    **dirs;
    char    *candidate;
    int     i;

    path = get_env_value("PATH", shell->env);
    if (!path || !*path)
    {
        free(path);
        return (NULL);
    }
    dirs = ft_split(path, ':');
    free(path);
    if (!dirs)
        return (NULL);
    i = 0;
    while (dirs[i])
    {
        candidate = join_path(dirs[i], name);
        if (candidate && access(candidate, X_OK) == 0)
        {
            i = 0;
            while (dirs[i])
                free(dirs[i++]);
            free(dirs);
            return (candidate);
        }
        free(candidate);
        i++;
    }
    i = 0;
    while (dirs[i])
        free(dirs[i++]);
    free(dirs);
    return (NULL);
}

int execute_external(t_cmd *cmd, t_shell *shell)
{
    pid_t   pid;
    int     status;
    char    *cmd_path;
    char    **envp;

    if (!cmd || !cmd->args || !cmd->args[0] || !shell)
        return (127);
    envp = env_list_to_envp(shell->env);
    if (!envp)
        return (1);
    if (ft_strchr(cmd->args[0], '/'))
        cmd_path = ft_strdup(cmd->args[0]);
    else
        cmd_path = find_program_on_path(cmd->args[0], shell);

    if (!cmd_path || access(cmd_path, X_OK) != 0)
    {
        if (!cmd_path)
            (void)0;
        else
            free(cmd_path);
        free_envp(envp);
        write(2, "minishell: external command not found\n", 36);
        return (127);
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        free(cmd_path);
        free_envp(envp);
        return (1);
    }
    if (pid == 0)
    {
        execve(cmd_path, cmd->args, envp);
        perror(cmd->args[0]);
        _exit(127);
    }
    waitpid(pid, &status, 0);

    free(cmd_path);
    free_envp(envp);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (128 + WTERMSIG(status));
}

int execute_command_node(t_ast *node , t_shell *shell)
{ 
    t_builtin_type builtin_type;

    if (!node || !node ->cmd || !node ->cmd ->args || !node ->cmd ->args[0])
        return (0); 
    builtin_type  = get_builtin_type(node ->cmd ->args[0]);

    if (builtin_type != BUILTIN_NONE)
        return (execute_builtin(node ->cmd, shell, builtin_type));
    return (execute_external(node->cmd, shell));
}











