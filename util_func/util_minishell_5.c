/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_minishell_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:15:28 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/06 22:03:47 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*ft_cmd_valid(char **env, char **cmd)
{
	int		i;
	char	*tmp;

	i = 0;
    if (!env)
        return (NULL);
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
			return (tmp);
		if (!access(cmd[0], X_OK | F_OK))
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

char	**get_envp(t_env_v *env)
{
	char	**envp;
	char	*tmp;
	char	*tmp1;
	int		i;
	int		size;

	i = 0;
	size = ft_lst_size(env);
	if (!env)
		return (NULL);
	envp = NULL;
	envp = malloc(sizeof(char *) * (size + 1));
	envp[size] = NULL;
	while (i < size)
	{
		tmp = ft_strdup(env->key);
		tmp = ft_charjoin(tmp, '=');
		tmp1 = ft_strjoin(tmp, env->value);
		envp[i] = tmp1;
		env = env->next;
		i++;
	}
	return (envp);
}

int	ft_lst_size(t_env_v *lst)
{
	int	i;

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

char	**ft_parce_env(char **env)
{
	int		i;
	int		index;
	char	**tab;

	index = ft_index(env, "PATH=");
	if (index < 0)
		return (NULL);
	tab = ft_split(env[index] + 5, ":");
	i = 0;
	while (tab[i])
	{
		tab[i] = ft_strjoin(ft_strdup(tab[i]), "/");
		i++;
	}
	return (tab);
}
