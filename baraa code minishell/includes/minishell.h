


typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				infile;
	int				outfile;
	int				is_builtin;
	struct s_cmd	*next;			
}	t_cmd;

t_token	*lexer(char *input);
void	print_tokens(t_token *tokens);
void	free_tokens(t_token *tokens);
t_cmd	*parser(t_token *tokens);
void	free_cmds(t_cmd *cmds);
int		executor(t_cmd *cmds, char **envp);
void	cleanup(t_token *tokens, t_cmd *cmds);



