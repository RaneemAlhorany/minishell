# ifndef TOKEN_LEXER
#define TOKEN_LEXER


typedef enum e_token_type {
    TOKEN_WORD, 
    TOKEN_PIPE, 
    TOKEN_REDIRECT_IN, 
    TOKEN_REDIRECT_OUT, 
    TOKEN_REDIRECT_APPEND, 
    TOKEN_HEREDOC 
} t_token_type;


typedef struct s_token {
    t_token_type type;
    char         *value;
    struct s_token *next;
} t_token;





#endif 

