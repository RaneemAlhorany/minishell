NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCS = -I. -I./Libft 

SRCS = lexer/lexer.c \
	lexer/lexer_utils.c \
	lexer/lexer_helper.c \
	lexer/token.c \
	expansion/expand.c \
	expansion/utils_expand.c \
	expansion/utils_expand_buffer.c \
	env/get_env_value.c \
	env/env.c \
	env/env_list.c \
	env/env_helper.c \
	parser/parser.c \
	parser/build_command_1.c \
	parser/build_command_2.c \
	parser/build_command_3.c \
	parser/parser_helper.c \
	parser/shared_method.c \
	parser/syntax_check_lexer_1.c \
	parser/syntax_check_lexer_2.c \
	signals/signals.c \
	signals/signals_utils.c \
	shell/shlvl.c \
	shell/shell_execution.c \
	shell/shell_free_1.c \
	shell/shell_free_2.c \
	shell/shell_helper_1.c \
	shell/shell_helper_2.c \
	shell/shell.c \
	main.c \
	execution/execute_ast.c \
	execution/execute_builtin.c \
	execution/execute_command_1.c \
	execution/execute_command_2.c \
	execution/execute_external_1.c \
	execution/execute_external_2.c \
	execution/execute_external_3.c \
	execution/execute_external_4.c \
	execution/execute_pipe_helper.c \
	execution/execute_pipe.c \
	execution/heardoc.c \
	execution/heardoc_helper_1.c \
	execution/heardoc_helper_2.c \
	execution/special_char.c \
	execution/redirections.c \
	execution/redirections_helper.c \
	execution/wildcard_1.c \
	execution/wildcard_2.c \
	execution/wildcard_3.c \
	execution/wildcard_4.c \
	execution/wildcard_5.c \
	execution/shared_method.c\
	execution/builtins/builtin_cd.c \
	execution/builtins/builtin_cd_helper.c \
	execution/builtins/builtin_echo.c \
	execution/builtins/builtin_echo_helper.c \
	execution/builtins/builtin_env.c \
	execution/builtins/builtin_env_helper.c \
	execution/builtins/builtin_exit.c \
	execution/builtins/builtin_exit_helper.c \
	execution/builtins/builtin_export_print.c \
	execution/builtins/builtin_export_options.c \
	execution/builtins/builtin_export_handle1.c \
	execution/builtins/builtin_export_handle2.c \
	execution/builtins/builtin_export.c \
	execution/builtins/builtin_pwd.c \
	execution/builtins/builtin_unset.c \
	execution/builtins/builtin_unset_helper.c \
	execution/builtins/shared_method.c

LIBFT = ./Libft/libft.a
OBJS = $(SRCS:.c=.o)

all: libft $(NAME)

libft:
	$(MAKE) -C ./Libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

%.o: %.C
	$(CC) $(CFLAGS) $(INCS) -x c -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

clean:
	rm -f $(OBJS)
	$(MAKE) -C ./Libft clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all


.PHONY:libft clean fclean re
