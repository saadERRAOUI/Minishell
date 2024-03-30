NAME = minishell

CFLAGS =  -Wall -Wextra -Werror  

CFILS = main.c

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