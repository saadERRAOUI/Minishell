/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_minishell_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:24:26 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/11 17:25:41 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
	@AUTHOR: Hicham BOUZID
	@PROTOTYPE: char *expand_or_not(char *ptr)
	@DESC: util for expanding env variables
	@DATE:
*/

//! low numbre of lines

static void	help(char *ptr, int *i)
{
	if (ptr[*i] == '\"')
	{
		(*i)++;
		while (ptr[*i])
		{
			if (ptr[*i] == '\"')
			{
				(*i)++;
				break ;
			}
			(*i)++;
		}
	}
	return ;
}

char	*expand_or_not(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '\"')
			help(ptr, &i);
		else if (ptr[i] == '\'')
		{
			i++;
			while (ptr[i] && ptr[i] != '\"')
			{
				if (ptr[i] == '$')
					ptr[i] = DL;
				i++;
			}
			i++;
		}
		else
			i++;
	}
	return (ptr);
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

char	*get_value(t_env_v *env, char *str)
{
	while (env)
	{
		if (!ft_strcmp(env->key, str))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	**ft_check_syntax(char *str)
{
	char	**ptr;
	int		i;

	i = 0;
	str = ft_convert_0(str);
	str = add_32(str, "|<>");
	ptr = ft_split(str, " \t");
	free(str);
	ptr = undo(ptr);
	i = 0;
	while (ptr[i])
	{
		ptr[i] = expand_or_not(ptr[i]);
		i++;
	}
	ptr = syntax(ptr);
	return (ptr);
}
