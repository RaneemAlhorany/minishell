
#include "minishell.h"


t_token* create_token(char *value , t_token_type type)
{
    t_token * token;

	token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token -> value = value ;
    token -> next = NULL;
    token -> type = type;

    return (token);
}


void append_token(t_token **head , t_token *new_token)
{
    t_token *temp;
	if (!new_token)
		return ;
    if (!*head)
        *head = new_token;
    else 
    {
        temp = *head;
        while (temp -> next)
            temp = temp -> next;
        temp -> next = new_token;        
    }
}


//////////////////////////////////////////////////////////////










