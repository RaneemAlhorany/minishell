


int execute_builtin(t_cmd *cmd, t_shell *shell, t_builtin_type type)
{
    if (!cmd || !shell)
        return (0);

    if (type == BUILTIN_ECHO)
        return builtin_echo(cmd, shell);
    else if (type == BUILTIN_CD)
       // return builtin_cd(cmd, shell);
    else if (type == BUILTIN_PWD)
       // return builtin_pwd(cmd, shell);
    else if (type == BUILTIN_EXPORT)
      //  return builtin_export(cmd, shell);
    else if (type == BUILTIN_UNSET)
      //  return builtin_unset(cmd, shell);
    else if (type == BUILTIN_ENV)
      //  return builtin_env(cmd, shell);
    else if (type == BUILTIN_EXIT)
      //  return builtin_exit(cmd, shell);
    return (0);
}




