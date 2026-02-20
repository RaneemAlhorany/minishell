#include "tree.h"

void free_ast(t_ast *node)
{
    if (!node)
        return ;
    free_ast(node->left);
    free_ast(node->right);
    free(node);
}
