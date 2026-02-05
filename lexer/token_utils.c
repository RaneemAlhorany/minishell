
void read_input (t_token token , char **argv)
{

}

void create_token(t_token *token)
{

    token -> value = NULL;
    token -> next = NULL;
    token -> type.TOKEN_WORD = NULL;

    token -> type.TOKEN_WORD = NULL;
    token -> type.TOKEN_PIPE = NULL;
    token -> type.TOKEN_REDIRECT_IN = NULL;
    token -> type.TOKEN_REDIRECT_OUT = NULL;
    token -> type.TOKEN_REDIRECT_APPEND = NULL;
    token -> type.TOKEN_HEREDOC = NULL;

}


     