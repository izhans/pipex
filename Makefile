#### Variables ####
NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT_DIR = libft/
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

# src
SRCS =	pipex.c
OBJS = $(SRCS:.c=.o)

#### Rules ####
# Declares rules
.PHONY: all clean fclean re

# Compiles project
all: $(NAME)

# Compiles .o files into executable
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# Compiles .c files into .o files
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

# Compiles libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Cleans .o files
clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

# Cleans all generated files
fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

# Cleans all and recompiles project
re: fclean all