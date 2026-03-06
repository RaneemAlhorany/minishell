




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







