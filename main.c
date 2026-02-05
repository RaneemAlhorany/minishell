#include "./minishell.h"


int main ()
{
    char *input = readline("minishell$ ");
    while (input[i])
    {
        skip_spaces();
        if (is_operator())
            handle_operator();
        else
            handle_word();
    }



}