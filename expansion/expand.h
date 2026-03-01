#ifndef EXPAND_H
# define EXPAND_H

# include <stdlib.h>
# include <string.h>
#include <stddef.h>
#include <sys/types.h>



typedef struct s_buffer
{
    char    *data;
    size_t  len;
    size_t  capacity;
}   t_buffer;


typedef struct s_expand
{
    char        *input;
    int         i;
    int         in_single;
    int         in_double;
    t_env       *env;
    int         last_status;
    t_buffer    buf;
}   t_expand;




 int  buffer_init(t_buffer *buf);
int  buffer_append_char(t_buffer *buf, char c);
int  buffer_append_str(t_buffer *buf, char *str);
 int  buffer_grow(t_buffer *buf, size_t needed);

int  init_expand(t_expand *ex,char *input, t_env *env, int last_status);
char *handle_env_variable(char *input, int *i, t_env *env);
char *handle_special_dollar(char *input, int *i, int last_status);
char    *expand_var(char *input, int *i, t_env *env, int last_status);

int  handle_quotes(t_expand *ex);
int  handle_expansion(t_expand *ex);
int  handle_regular_char(t_expand *ex);
int  process_expand(t_expand *ex);
char    *expand_string(char *input,t_env *env, int last_status);

#endif
