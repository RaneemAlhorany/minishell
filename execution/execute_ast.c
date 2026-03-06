



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








