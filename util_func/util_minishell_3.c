/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_minishell_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:23:09 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/12 01:10:25 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
	@AUTHOR: hicham bouzid
	@PROTOTYPE: int ft_strlen_until(char *str, char c)
	@DESC: function like strchr but this return the index
	@DATE: 16-04-2024
*/

int	ft_strlen_until(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (str[i + 1])
				return (i + 1);
			else
				return (-1);
		}
		i++;
	}
	return (-1);
}

/*
	@AUTHOR: Hicham BOUZID
	@PROTOTYPE: char	*get_measurements(int *index, int *len, char *ptr)
	@DESC: function uset to get index of start and end of env variable
	@DATE: 18-04-2024
*/

char	*get_measurements(int *index, int *len, char *ptr)
{
	*index = ft_strlen_until(ptr, '$');
	if (ptr[*index] == '?')
		return (NULL);
	*len = *index;
	while (ptr[*len])
	{
		if (ptr[*len] == '\"' || ptr[*len] == ' ' || ptr[*len] == '\'')
			break ;
		(*len)++;
	}
	return (ft_substr(ptr, *index, *len - *index));
}

static char	*ft_help(char *ptr, int index)
{
	char	*tmp;
	char	*s2;

	tmp = ft_itoa(g_exit);
	s2 = ft_modifie(ptr, index, index + 1, tmp);
	free(tmp);
	return (s2);
}
/*
	@AUTOR: hicham bouzid
	@PRORTOTYPE: char	*ft_replace_dollar(char *ptr, t_env_v *env)
	@DESC: just check if the env variable found and replace it else
	remove the word containe $ from the string
	@DATE: 18-05-2024
*/

char	*ft_replace_dollar(char *ptr, t_env_v *env)
{
	char	*s1;
	char	*s2;
	int		index;
	int		len;

	s2 = NULL;
	if (ft_strlen_until(ptr, '$') != -1)
	{
		s1 = get_measurements(&index, &len, ptr);
		if (!s1)
			return (ft_help(ptr, index));
		s1 = ft_substr(ptr, index, len - index);
		while (env)
		{
			if (!ft_strcmp(env->key, s1))
			{
				s2 = env->value;
				break ;
			}
			env = env->next;
		}
		free(s1);
		return (ft_modifie(ptr, index, len, s2));
	}
	return (NULL);
}

char	**ft_split_2(char *s, char c)
{
	char	**ptr;
	int		i;
	char	*str;

	(void)c;
	ptr = malloc(sizeof(char *) * 3);
	if (!ptr)
		return (NULL);
	str = ft_strdup(s);
	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	str[i++] = 0;
	ptr[0] = ft_strdup(str);
	ptr[1] = ft_strdup(str + i);
	ptr[2] = NULL;
	return (free(str), ptr);
}
