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
parser/parser_utils.c \
parser/build_command_1.c \
parser/build_command_2.c \
parser/parser_helper.c\
parser/syntax_check_lexer \
A_edit_that_we_will_use_it_in_the_futeure/src/executor/executor.c \
A_edit_that_we_will_use_it_in_the_futeure/utils/free.c \
A_edit_that_we_will_use_it_in_the_futeure/src/builtins/exit.c \
black_box_project/pipex/utils_bonus.c \
black_box_project/pipex/pipe_and_fork_bonus.c \
black_box_project/pipex/handel_errors_bonus_1.c \
black_box_project/pipex/handel_errors_bonus_2.c \
black_box_project/pipex/files_bonus.c \
A_edit_that_we_will_use_it_in_the_futeure/src/tree/tree_bulld.c \
A_edit_that_we_will_use_it_in_the_futeure/src/tree/tree_exec.c \
A_edit_that_we_will_use_it_in_the_futeure/src/tree/tree_free.c \
main.c

LIBFT = black_box_project/Libft/libft.a


all: libft $(NAME)


libft:
	$(MAKE) -C black_box_project/Libft

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

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
