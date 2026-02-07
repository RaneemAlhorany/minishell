NAME        = minishell

CC          = cc

CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -Iincludes -Ilibft

SRC_DIR     = src
OBJ_DIR     = obj
LIBFT_DIR   = libft

LIBFT       = $(LIBFT_DIR)/libft.a

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/lexer/lexer.c \
	$(SRC_DIR)/lexer/token.c \
	$(SRC_DIR)/parser/parser.c \
	$(SRC_DIR)/executor/executor.c \
	$(SRC_DIR)/executor/pipe.c \
	$(SRC_DIR)/executor/redirection.c \
	$(SRC_DIR)/builtins/cd.c \
	$(SRC_DIR)/builtins/echo.c \
	$(SRC_DIR)/builtins/env.c \
	$(SRC_DIR)/builtins/exit.c \
	$(SRC_DIR)/builtins/export.c \
	$(SRC_DIR)/builtins/pwd.c \
	$(SRC_DIR)/builtins/unset.c \
	$(SRC_DIR)/signals/signals.c \
	$(SRC_DIR)/utils/error.c \
	$(SRC_DIR)/utils/free.c \

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
