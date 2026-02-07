#include "minishell.h"



// im here complete the following method and compare it with baraa code 
//! after complete method add it to header file 
t_token *word_detection (char **input)
{
save start position
while current char exists
    if quote
        enter quote mode
        read until same quote
    else if space or operator
        break
    else
        read char
create WORD token from collected chars
}