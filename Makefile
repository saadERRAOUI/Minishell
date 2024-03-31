NAME = minishell

CFLAGS =  -Wall -Wextra -Werror  

LIBFT_DIR = ./libft

# Find all .c files recursively in the ./libft directory
LIBFT_C_FILES = $(shell find $(LIBFT_DIR) -type f -name '*.c')

# Add the found .c files to your source list
# LIBFT_C_SOURCES = $(wildcard *.c) $(LIBFT_C_FILES)

CFILS = $(wildcard *.c) $(LIBFT_C_FILES) ./util_func/util_0.c ./util_func/util_1.c 
#minishell.c minishell_constructors.c minishell_parsers.c $(LIBFT_C_SOURCES) \

OBJS = $(CFILS:.c=.o)

 # without -lreadline flag the compilation will be failed
 
$(NAME): $(OBJS)
	cc  -lreadline $(OBJS) -o $(NAME) 

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all