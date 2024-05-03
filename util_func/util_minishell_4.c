/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_minishell_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:24:26 by hibouzid          #+#    #+#             */
/*   Updated: 2024/04/27 17:05:55 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
	@AUTHOR: Hicham BOUZID
	@PROTOTYPE: char *expand_or_not(char *ptr)
	@DESC: util for expanding env variables
	@DATE:
*/
char	*expand_or_not(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '\"')
		{
			i++;
			while (ptr[i])
			{
				if (ptr[i] == '\"')
				{
					i++;
					break ;
				}
				i++;
			}
		}
		else if (ptr[i] == '\'')
		{
			i++;
			while (ptr[i])
			{
				if (ptr[i] == '\'')
				{
					i++;
					break ;
				}
				if (ptr[i] == '$')
					ptr[i] = DL;
				i++;
			}
		}
		else
			i++;
	}
	return (ptr);
}

/*
	@AUTHOR: Hicham BOUZID
	@PROTOTYPE: int	ft_strleen(char **ptr)
	@DESC: count lenght of an array tow dimention
	@DATE: 21-04-2024
*/

int	ft_strleen(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

/*
	@AUTHOR: Hicham BOUZID
	@PROTORTPE: char	**ft_free(int index, char **ptr)
	@DESC: fucntion free an array tow dimention
	@DATE: 	21-04-2024
*/

char	**ft_free(int index, char **ptr)
{
	while (index >= 0)
	{
		free(ptr[index]);
		index--;
	}
	free(ptr);
	return (0);
}

// char	*ft_cmd_valid(t_env_v **env, char **cmd)
// {
// 	char **path;


// 	if (!access(*cmd, F_OK | X_OK))
// 		return (ft_strdup(*cmd));

// 	while
// }

// char *get_path(char **ptr, t_env_v *env)
// {
// 	i
// }

char *get_value(t_env_v *env,char *str)
{
	while (env)
	{
		if (!ft_strcmp(env->key, str))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

// char	**ft_parce_env(t_env_v *env)
// {
// 	int		i;
// 	// int		index;
// 	char	*tmp;
// 	char	**tab;

// 	tmp = get_value(env, "PATH");
// 	// index = ft_index(env, "PATH=");
// 	if (!tmp)
// 		return (NULL);
// 	tab = ft_split(tmp, ":");
// 	i = 0;
// 	while (tab[i])
// 	{
// 		tmp = tab[i];
// 		tab[i] = ft_strjoin(tab[i], "/");
// 		free(tmp);
// 		i++;
// 	}
// 	return (tab);
// }

static int	ft_index(char **envp, char *str)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], str, ft_strlen(str)))
			return (i);
		i++;
	}
	return (-1);
}

char	**ft_parce_env(char **env)
{
	int		i;
	int		index;
	// char	*tmp;
	char	**tab;

	index = ft_index(env, "PATH=");
	if (index < 0)
	{
		// tab = malloc(sizeof(char *));
		// tab = 0;
		return (NULL);
	}
	tab = ft_split(env[index] + 5, ":");
	i = 0;
	while (tab[i])
	{
		// tmptab[i];
		tab[i] = ft_strjoin(ft_strdup(tab[i]), "/");
		// free(tmp);
		i++;
	}
	return (tab);
}

char *ft_cmd_valid(char **env, char **cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	if ((!ft_strncmp(cmd[i], ".", 1) || !ft_strncmp(cmd[i], "./", 2))
		|| (!ft_strncmp(cmd[i], "/", 1) && access(cmd[0], X_OK | F_OK)))
		return (NULL);
	if (!access(cmd[0], F_OK | X_OK))
		return (ft_strdup(cmd[0]));
	while (env[i])
	{
		if (env)
			tmp = ft_strjoin(env[i], cmd[0]);
		if (tmp && !access(tmp, X_OK | F_OK))
		{
			// free(tmp);÷
			return (tmp);
		}
		if (!access(cmd[0], X_OK | F_OK))
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

char **get_envp(t_env_v *env)
{
	char **envp;
	char *tmp;
	char *tmp1;
	int i;
	int size;

	i = 0;
	
	size = ft_lst_size(env);
	if (!env)
		return (NULL);
	envp = NULL;
	envp = malloc(sizeof(char *) * (size + 1));
	// printf("---------------> %d\n", size);
	envp[size] = NULL;
	while (i < size)
	{
		tmp = ft_strdup(env->key);	
		tmp = ft_charjoin(tmp ,'=');
		tmp1 = ft_strjoin(tmp, env->value);
		envp[i] = tmp1;
		env = env->next;
		i++;
	}
	// printf("---------------> %d\n", i);
	return (envp);
}

int	ft_lst_size(t_env_v *lst)
{
	int i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

// char **get_path_env(t_env_v *env, char **path, char **argv)
// {
// 	char **envp;
// 	// char **ptr;
// 	(void)path;
// 	(void)argv;
// 	envp = get_envp(env);
// 	// if (!envp)
		
// 	// for (int i = 0; envp[i]; i++)
// 	// 	printf("================= %s\n", envp[i]);
// 		// printf("================= %s\n", argv[0]);
// 	if (envp)
// 	{
// 		path = ft_parce_env(envp);
// 		*path = ft_cmd_valid(path, argv);
// 		// printf("%s\n", *path);
// 	}
// 	return (envp);
// }