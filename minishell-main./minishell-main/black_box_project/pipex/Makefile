CC      = cc
CFLAGS  = -Wall -Wextra -Werror

NAME    = pipex

LIBFT_DIR = ./Libft
LIBFT     = $(LIBFT_DIR)/libft.a

MANDATORY_FLAG = .mandatory
BONUS_FLAG     = .bonus

# ======================= SOURCES =======================

MANDATORY_SRC = \
	main.c \
	files.c \
	handel_errors.c \
	pipe_and_fork.c \
	utils.c

BONUS_SRC = \
	main_bonus.c \
	files_bonus.c \
	utils_bonus.c \
	pipe_and_fork_bonus.c \
	handel_errors_bonus_1.c \
	handel_errors_bonus_2.c \
	handel_here_doc_bonus.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c

MANDATORY_OBJ = $(MANDATORY_SRC:.c=.o)
BONUS_OBJ     = $(BONUS_SRC:.c=.o)

# ======================= RULES =======================

all: $(MANDATORY_FLAG)

bonus: $(BONUS_FLAG)

$(MANDATORY_FLAG): $(MANDATORY_OBJ) $(LIBFT)
	rm -f $(BONUS_FLAG)
	$(CC) $(CFLAGS) $(MANDATORY_OBJ) $(LIBFT) -o $(NAME)
	touch $(MANDATORY_FLAG)

$(BONUS_FLAG): $(BONUS_OBJ) $(LIBFT)
	rm -f $(MANDATORY_FLAG)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $(NAME)
	touch $(BONUS_FLAG)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ======================= CLEAN =======================

clean:
	rm -f $(MANDATORY_OBJ) $(BONUS_OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(MANDATORY_FLAG) $(BONUS_FLAG)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re