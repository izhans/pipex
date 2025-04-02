# Variables
NAME = libft.a
CC = cc
FLAGS = -Wall -Werror -Wextra

# Math
MATH_FOLDER = math/
MATH_SRCS = \
			ft_abs.c
MATH_OBJS = $(MATH_SRCS:.c=.o)

# Lists
LISTS_FOLDER = lists/
LISTS_SRCS = \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c
LISTS_OBJS = $(LISTS_SRCS:.c=.o)

# Char
CHAR_FOLDER = char/
CHAR_SRCS = \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_tolower.c \
			ft_toupper.c
CHAR_OBJS = $(CHAR_SRCS:.c=.o)

# String
STRING_FOLDER = string/
STRING_SRCS = \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strcpy.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c
STRING_OBJS = $(STRING_SRCS:.c=.o)

# Memory
MEMORY_FOLDER = memory/
MEMORY_SRCS = \
			ft_bzero.c \
			ft_calloc.c \
			ft_free_str_array.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c
MEMORY_OBJS = $(MEMORY_SRCS:.c=.o)

# Parse
PARSE_FOLDER = parse/
PARSE_SRCS = \
			ft_atoi.c \
			ft_itoa.c \
			ft_number_len.c
PARSE_OBJS = $(PARSE_SRCS:.c=.o)

# Write
WRITE_FOLDER = write/
WRITE_SRCS = \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putendl.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_putstr.c
WRITE_OBJS = $(WRITE_SRCS:.c=.o)

OBJ = $(MATH_OBJS) $(LISTS_OBJS) $(CHAR_OBJS) $(STRING_OBJS) $(MEMORY_OBJS) $(PARSE_OBJS) $(WRITE_OBJS)

# Rules
.PHONY: all clean fclean re bonus

# Compiles libft
all: $(NAME)

# Creates libft.a from .o files
$(NAME): libft.h $(OBJ)
	ar -r $(NAME) $(OBJ)

# Compiles .c files into .o files
$(MATH_OBJS): $(addprefix $(MATH_FOLDER), $(MATH_SRCS))
	$(CC) $(FLAGS) -c $(addprefix $(MATH_FOLDER), $(MATH_SRCS))

$(LISTS_OBJS): $(addprefix $(LISTS_FOLDER), $(LISTS_SRCS))
	$(CC) $(FLAGS) -c $(addprefix $(LISTS_FOLDER), $(LISTS_SRCS))

$(CHAR_OBJS): $(addprefix $(CHAR_FOLDER), $(CHAR_SRCS))
	$(CC) $(FLAGS) -c $(addprefix $(CHAR_FOLDER), $(CHAR_SRCS))

$(STRING_OBJS): $(addprefix $(STRING_FOLDER), $(STRING_SRCS))
	$(CC) $(FLAGS) -c $(addprefix $(STRING_FOLDER), $(STRING_SRCS))

$(MEMORY_OBJS): $(addprefix $(MEMORY_FOLDER), $(MEMORY_SRCS))
	$(CC) $(FLAGS) -c $(addprefix $(MEMORY_FOLDER), $(MEMORY_SRCS))

$(PARSE_OBJS): $(addprefix $(PARSE_FOLDER), $(PARSE_SRCS))
	$(CC) $(FLAGS) -c $(addprefix $(PARSE_FOLDER), $(PARSE_SRCS))

$(WRITE_OBJS): $(addprefix $(WRITE_FOLDER), $(WRITE_SRCS))
	$(CC) $(FLAGS) -c $(addprefix $(WRITE_FOLDER), $(WRITE_SRCS))

# Cleans temporary files but not the executable
clean:
	rm -f $(OBJ)

# Cleans the same as clean + the executable (full clean)
fclean: clean
	rm -f $(NAME)

# Cleans and recompiles the libft
re: fclean all
