#ifdef BUILTIN_H
#define BUILTIN_H 

#include <unistd.h>

int  parse_n_flag(char **args, int *index);
void print_echo_args(char **args, int index);
int builtin_echo(t_cmd *cmd, t_shell *shell);


#endif

