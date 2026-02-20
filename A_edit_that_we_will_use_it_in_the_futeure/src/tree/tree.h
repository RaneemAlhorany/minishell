#ifndef TREE_H
# define TREE_H

# include "minishell.h"

typedef struct s_cmd t_cmd; // بحتج اعرفها هون بس ما راح استخدمها لانه مستخدمه بمكان ثاني و ما راح اعمل لها include لانه راح يسبب مشاكل في ال include المتبادل بين الملفات


typedef enum e_node_type
{
    NODE_CMD,
    NODE_PIPE
}   t_node_type;

typedef struct s_ast// Abstract Syntax Tree
{
    t_node_type        type;
    t_cmd              *cmd;
    struct s_ast       *left;
    struct s_ast       *right;
}   t_ast;


t_ast *build_ast_from_cmds(t_cmd *cmds);
t_ast *new_cmd_node(t_cmd *cmd);
t_ast *new_pipe_node(t_ast *left, t_ast *right);

void free_ast(t_ast *node);

int execute_ast(t_ast *node, char **envp);
int spawn_left_pipe(t_ast *node, char **envp, int fd[2], pid_t *left_pid);
int spawn_right_pipe(t_ast *node, char **envp, int fd[2], pid_t *right_pid);
int exec_pipe_node(t_ast *node, char **envp);
#endif
