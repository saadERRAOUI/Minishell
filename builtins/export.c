/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:40:47 by serraoui          #+#    #+#             */
/*   Updated: 2024/04/25 11:06:55 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static t_env_v	*ft_content_equal(t_env_v **env, char *s)
{
	t_env_v	*tmp;
	size_t	l;
	size_t	len;

	tmp = (*env);
	len = ft_strlen(s);
	while (tmp)
	{
		if (len > ft_strlen(tmp->key))
			l = len;
		else
			l = ft_strlen(tmp->key);
		if (!ft_strncmp(tmp->key, s, l))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	ft_export_envs(t_env_v **env)
{
	t_env_v	*tmp;

	tmp = (*env);
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

static void	ft_hdl_case(t_env_v **env, char **_s, t_env_v *node)
{
	if (_s[0][ft_strlen(_s[0]) - 1] == '+')
	{
		_s[0][ft_strlen(_s[0]) - 1] = '\0';
		node = ft_content_equal(env, _s[0]);
		node->value = ft_strjoin(ft_strdup(node->value), _s[1]);
	}
	else
	{
		(*node) = (t_env_v){_s[0], _s[1], NULL};
		ft_lstadd_back(env, node);
	}
}

void	ft_export(t_env_v **env, char *s)
{
	char	**_s;
	t_env_v	*node;

	if (!s)
		return (ft_export_envs(env));
	_s = ft_split_2(s, '=');
	if (!_s)
		return ;
	node = malloc(sizeof(t_env_v));
	if (count_words(s, '=') >= 2)
		ft_hdl_case(env, _s, node);
	else if (count_words(s, '=') == 1 && ft_strchr(s, '='))
	{
		if (_s[0][ft_strlen(_s[0]) - 1] == '+')
			_s[0][ft_strlen(_s[0]) - 1] = '\0';
		if (ft_content_equal(env, _s[0]))
			return (ft_free(0, _s), free(node));
		(*node) = (t_env_v){_s[0], " ", NULL};
		ft_lstadd_back(env, node);
	}
	else
	{
		free(_s[0]);
		free(node);
	}
	free(_s);
}
