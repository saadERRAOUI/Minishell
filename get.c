#include "minishell.h"

t_env_v	*env_init(char **env)
{
	t_env_v	*envs;
	t_env_v	*node;
	int		i;
	char	**s;

	if (!env)
		return (NULL);
	envs = NULL;
	i = 0;
	while (env[i])
	{
		node = (t_env_v *)malloc(sizeof(t_env_v));
		s = ft_split_2(env[i], '=');
		if (s) //! fix else case !
			(*node) = (t_env_v){s[0], s[1], NULL};
		ft_lstadd_back(&envs, node);
		free(s);
		i++;
	}
	return (envs);
}

// char *add_$$(char *str, t_env_v *env)
// {
// 	int i;
// 	char c;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\"')
// 		c = str[i];
// 		i++;
// 		while (str[i] != c & str[i])
// 		{

// 		}
// 	}
// }

int	main(int ac, char **av, char **envp)
{
	// char *tab = add_32(av[1], "<>|");
	// printf("---> :%s\n", tab);
	t_env_v *env;

	env = env_init(env);
	char **tab =
}