NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCS = -I. -I./Libft 

# Source files
SRCS = lexer/lexer.c \
	lexer/lexer_utils.c \
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
	parser/parser_helper_1.c \
	parser/parser_helper_2.c \
	parser/syntax_check_lexer_1.c \
	parser/syntax_check_lexer_2.c \
	parser/syntax_check_lexer_3.c \
	signals/signals.c \
	signals/signals_utils.c \
	shell/shell.c \
	shell/helper_1.c \
	shell/helper_2.c \
	shell/helper_3.c \
	shell/helper_4.c \
	shell/helper_5.c \
	main.c \
	execution/execute_ast.c \
	execution/execute_builtin.c \
	execution/execute_command.c \
	execution/execute_external.c \
	execution/execute_pipe_helper.c \
	execution/execute_pipe.c \
	execution/heardoc.c \
	execution/helper_execution_1.c \
	execution/helper_execution_2.c \
	execution/helper_execution_3.c \
	execution/redirections.c \
	execution/builtins/builtin_cd.c \
	execution/builtins/builtin_cd_helper.c \
	execution/builtins/builtin_echo.c \
	execution/builtins/builtin_echo_helper_1.c \
	execution/builtins/builtin_echo_helper_2.c  \
	execution/builtins/builtin_env.c \
	execution/builtins/builtin_exit.c \
	execution/builtins/builtin_exit_helper_1.c \
	execution/builtins/builtin_exit_helper_2.c \
	execution/builtins/builtin_exit_helper_3.c \
	execution/builtins/builtin_export_helper1.c \
	execution/builtins/builtin_export_helper2.c \
	execution/builtins/builtin_export_helper3.c \
	execution/builtins/builtin_export_helper4.c \
	execution/builtins/builtin_export.c \
	execution/builtins/builtin_pwd.c \
	execution/builtins/builtin_unset.c \
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

test: all
	bash tests/run_required_tests.sh

test-long: all
	RUN_LONG_TESTS=1 bash tests/run_required_tests.sh

.PHONY: all libft clean fclean re test test-long
