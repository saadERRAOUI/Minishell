/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:40:47 by serraoui          #+#    #+#             */
/*   Updated: 2024/05/13 01:44:27 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static int	is_valid_name(char *s)
{
	int		i;
	char	*s_rep;

	if (!s)
		return (0);
	i = 0;
	s_rep = ft_strdup(s);
	if (s_rep[ft_strlen(s) - 1] == '+')
		s_rep[ft_strlen(s) - 1] = '\0';
	if (!ft_isalpha(s_rep[0]) && s_rep[0] != '_')
		return (0);
	while (s_rep[i])
	{
		if (!ft_isalnum(s_rep[i]) && s_rep[i] != '_')
			return (free(s_rep), 0);
		i++;
	}
	return (free(s_rep), 1);
}

static int	util_export(t_env_v **env, char **s, int flag)
{
	t_env_v	*node;

	if (ft_content_equal(env, s[0]))
	{
		node = ft_content_equal(env, s[0]);
		if (flag && s[1])
			node->value = ft_strjoin(node->value, s[1]);
		else if (!flag)
		{
			free(node->value);
			node->value = selectt(s[1]);
		}
	}
	else if (!ft_content_equal(env, s[0]))
	{
		node = (t_env_v *)malloc(sizeof(t_env_v));
		if (s[1])
			(*node) = (t_env_v){ft_strdup(s[0]), ft_strdup(s[1]), NULL};
		else
			(*node) = (t_env_v){ft_strdup(s[0]), ft_strdup(" "), NULL};
		ft_lstadd_back(env, node);
	}
	else
		return (0);
	return (1);
}

static int	export_arg_value(t_env_v **env, char **s)
{
	int	flag;

	flag = 0;
	if (!env || !*env)
		return (0);
	if (s[0] && s[0][ft_strlen(s[0]) - 1] == '+')
	{
		s[0][ft_strlen(s[0]) - 1] = '\0';
		flag = 1;
	}
	if (!util_export(env, s, flag))
		return (0);
	return (1);
}

static int	export_argument(t_env_v **env, char *av)
{
	char	**s;

	s = ft_split_2(av, '=');
	if (!s)
		return (0);
	if (!is_valid_name(s[0]))
	{
		g_exit = 1;
		ft_putstr_fd("bash: export: '", 2);
		ft_putstr_fd(av, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (ft_free(ft_strleen(s), s), 0);
	}
	if (!export_arg_value(env, s))
		return (ft_free(ft_strleen(s), s), 0);
	g_exit = 0;
	return ((ft_free(ft_strleen(s), s), 1));
}

void	ft_export(t_env_v **env, char **av)
{
	int	flag;

	flag = 0;
	if (av && !av[1])
	{
		g_exit = 0;
		return (ft_export_envs(env));
	}
	av++;
	while (*av)
	{
		if (!export_argument(env, (*av)))
		{
			flag = 1;
			break ;
		}
		av++;
	}
	if (!flag)
		g_exit = 0;
}
