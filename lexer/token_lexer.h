# ifndef TOKEN_LEXER
#define TOKEN_LEXER


# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef enum e_token_type {
    TOKEN_WORD, 
    TOKEN_PIPE,               // |
    TOKEN_REDIRECT_IN,        // <
    TOKEN_REDIRECT_OUT,       // >
    TOKEN_REDIRECT_APPEND,    // >>
    TOKEN_HEREDOC             // <<
} t_token_type;



typedef struct s_token {
    t_token_type         type;
    char                *value;
    struct s_token      *next;
} t_token;



t_token* create_token(char *value , t_token_type type);
void append_token(t_token **head , t_token *new_token);
void skip_spaces(char **input);
t_token *detect_double_operator(char **input);
t_token *detect_single_operator(char **input);
t_token *operator_detection(char **input);
int  move_through_word(char **input);
t_token *word_detection(char **input);
t_token *lexer (char *input);







//////////////////////////////////////////////////////////////////
// add the test methods bellow : 




#endif 

