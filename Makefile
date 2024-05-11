NAME = minishell

CFLAGS = -Wall -Wextra -Werror  -I/Users/serraoui/.brew/opt/readline/include
LDFLAGS =  -lreadline -L/Users/serraoui/.brew/opt/readline/lib

CFILS = ./util_func/util_0.c ./util_func/util_1.c ./libft/ft_atoi.c ./libft/ft_bzero.c\
		./libft/ft_calloc.c ./libft/ft_isalnum.c ./libft/ft_isalpha.c ./libft/ft_isascii.c\
		./libft/ft_isdigit.c ./libft/ft_isprint.c ./libft/ft_itoa.c ./libft/ft_lstadd_front_bonus.c\
		./libft/ft_lstclear_bonus.c ./libft/ft_lstdelone_bonus.c ./libft/ft_lstiter_bonus.c\
		./libft/ft_lstnew_bonus.c ./libft/ft_lstsize_bonus.c ./libft/ft_memchr.c ./libft/ft_memcmp.c\
		./libft/ft_memcpy.c ./libft/ft_memmove.c ./libft/ft_memset.c ./libft/ft_putchar_fd.c ./libft/ft_putendl_fd.c\
		./libft/ft_putnbr_fd.c ./libft/ft_putstr_fd.c ./libft/ft_split.c ./libft/ft_strchr.c\
		./libft/ft_strdup.c ./libft/ft_striteri.c ./libft/ft_strjoin.c ./libft/ft_strlcat.c\
		./libft/ft_strlcpy.c ./libft/ft_strlen.c ./libft/ft_strmapi.c ./libft/ft_strncmp.c\
		./libft/ft_strnstr.c ./libft/ft_strrchr.c ./libft/ft_strtrim.c ./libft/ft_substr.c\
		./libft/ft_tolower.c ./libft/ft_toupper.c minishell.c minishell_constructors.c\
		minishell_parsers.c ./util_func/util_2.c ./util_func/lexer.c ./builtins/echo.c\
		./builtins/export.c ./builtins/cd.c ./builtins/exit.c ./builtins/unset.c ./builtins/env.c ./builtins/pwd.c\
		./util_func/util_minishell_3.c ./util_func/util_minishell_4.c ./util_func/util_minishell_5.c\
		./util_func/util_minishell_6.c free_tree.c minishell_signals.c

OBJS = $(CFILS:.c=.o)

#-fsanitize=address -g3

$(NAME): $(OBJS)
	cc    $(OBJS)  $(LDFLAGS) -o $(NAME)

all: $(NAME)


clean:
	rm -rf $(OBJS)
	clear

fclean: clean
	rm -rf $(NAME)
	clear

re: fclean all
