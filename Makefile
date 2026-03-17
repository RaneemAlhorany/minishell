NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCS = -I. -Iblack_box_project/Libft -Iblack_box_project/pipex

# Source files
SRCS = lexer/lexer.c \
lexer/lexer_utils.c \
lexer/token.c \
expansion/expand.c \
expansion/utils_expand.c \
expansion/utils_expand_buffer.c \
env/get_env_value.c \
parser/parser.c \
parser/build_command_1.c \
parser/build_command_2.c \
parser/build_command_3.c \
parser/parser_helper.c\
parser/syntax_check_lexer.c \
black_box_project/pipex/utils_bonus.c \
black_box_project/pipex/pipe_and_fork_bonus.c \
black_box_project/pipex/handel_errors_bonus_1.c \
black_box_project/pipex/handel_errors_bonus_2.c \
black_box_project/pipex/files_bonus.c \
shell/shell.c \
env/env_list.c \
env/env_helper.c \
execution/execute_builtin.c \
main.c \
execution/execute_ast.c \
execution/builtins/builtin_cd.c \
execution/builtins/builtin_cd_helper.c \
execution/builtins/builtin_echo.c \
execution/builtins/builtin_env.c \
execution/builtins/builtin_env_helper.c \
execution/builtins/builtin_exit.c \
execution/builtins/builtin_export_helper.c \
execution/builtins/builtin_export_helper2.c \
execution/builtins/builtin_export.c \
execution/builtins/builtin_pwd.c \
execution/builtins/builtin_unset.c\
execution/builtins/shared_method.c\
execution/execute_command.c
LIBFT = black_box_project/Libft/libft.a

all: libft $(NAME)


libft:
	$(MAKE) -C black_box_project/Libft

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

%.o: %.C
	$(CC) $(CFLAGS) $(INCS) -x c -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

clean:
	rm -f $(OBJS)
	$(MAKE) -C black_box_project/Libft clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all libft clean fclean re
