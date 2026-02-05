


//! THIS METHOD USE TO CREATE TOKEN THAT WILL USED FOR INPUT
t_token* create_token(char *value , t_token_type type)
{
    t_token * token;

    token = malloc (sizeof(t_token));
    if (!token)
        return (NULL);

    token -> value = value ;
    token -> next = NULL;
    token -> type = type;

    return (token);
}


//////////////////////////////////////////////////////////////
