



int execute_ast(t_ast *node , t_shell *shell) 
{
    if (!node)
        return (0);

    if (node ->type == COMMAND)
        return (execute_command_node(node, shell));
//    else if (node ->type == PIPE)
//        return execute_pipe_node(node, shell);
    return 0;
}


int execute_command_node (t_ast *node , t_shell *shell)
{ 
    t_builtin_type builtin_type;
    if (!node || !node ->cmd || !node ->cmd ->args || !node ->cmd ->args[0])
        return (0); 
    builtin_type  = get_builtin_type(node ->cmd ->args[0]);

    if (builtin_type != BUILTIN_NONE)
        return (execute_builtin(node ->cmd, shell, builtin_type));    
    else
 //       return (execute_external(node, shell));

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





