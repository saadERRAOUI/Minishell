#include "minishell.h"

int main(int ac, char **av)
{
	char **ptr = ft_split("\"ls-l\"  | wc", " \t\v\r\f");
	for (int i = 0; ptr[i]; i++)
		printf("--> %s\n", ptr[i]);
}