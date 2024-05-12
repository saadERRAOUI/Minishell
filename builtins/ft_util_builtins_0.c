/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_builtins_0.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 00:59:01 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/12 01:17:46 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_v	*ft_content_equal(t_env_v **env, char *s)
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

void	ft_export_envs(t_env_v **env)
{
	t_env_v	*tmp;

	tmp = (*env);
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

/*
	@AUTHOR: Hicham BOUZID
	@PROTOTYPE: char **ft_expand(char **ptr, t_env_v *env)
	@DESC: this function check if the string containe an env variable
		and replacet at the last remove ' & "
	@DATE: 19-04-2024
*/
char	**ft_expand(char **ptr, t_env_v *env)
{
	int	i;
	int	j;

	i = 0;
	ptr = add_dollar(ptr, env);
	while (ptr[i])
	{
		j = 0;
		while (ptr[i][j])
		{
			if (ptr[i][j] == 7)
				ptr[i][j] = '$';
			j++;
		}
		i++;
	}
	i = 0;
	while (ptr[i])
	{
		ptr[i] = ft_shift(ptr[i]);
		i++;
	}
	return (ptr);
}
