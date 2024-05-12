/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:22:40 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/12 01:10:13 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
	@AUTHOR: hicham bouzid
	@DESC: check if chars in sym are syparde by space
	if not add space
	@PROTOTYPE: char *add_32(char *str, char *sym)
	@DATE: 03-04-2023
*/

char	*add_32(char *str, char *sym)
{
	int		i;
	char	*ptr;

	ptr = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (i == 0 && ft_strchr(sym, str[i]))
		{
			ptr = ft_charjoin(ptr, str[i]);
			if (!ft_strchr(sym, str[i + 1]))
				ptr = ft_charjoin(ptr, 32);
		}
		else if ((!ft_strchr(sym, str[i]) && i < (int)ft_strlen(str)
				&& ft_strchr(sym, str[i + 1])) || (ft_strchr(sym, str[i])
				&& i < (int)ft_strlen(str) && !ft_strchr(sym, str[i + 1])))
		{
			ptr = ft_charjoin(ptr, str[i]);
			ptr = ft_charjoin(ptr, 32);
		}
		else
			ptr = ft_charjoin(ptr, str[i]);
		i++;
	}
	return (ptr);
}

static void	help(char *ptr, int *i, int *j, char *str)
{
	char	c;

	c = ptr[*i];
	(*i)++;
	while (ptr[*i])
	{
		if (ptr[*i] == c)
		{
			(*i)++;
			break ;
		}
		else
			str[(*j)++] = ptr[(*i)++];
	}
}

/*
	@AUTHOR: hicham bouzid
	@DESC: remove " and ' by shif the string
	@PROTOTYPE: char *ft_shift(char *ptr)
	@DATE: 04-04-2024
*/

char	*ft_shift(char *ptr)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = ft_strdup(ptr);
	while (ptr[i])
	{
		if (ptr[i] == '\'' || ptr[i] == '\"')
		{
			help(ptr, &i, &j, str);
		}
		else
			str[j++] = ptr[i++];
	}
	str[j] = 0;
	free(ptr);
	return (str);
}

/*
	@AUTHOR: Hicham BOUZID
	@DESC: function util used just in this file
	@DATE: 22-04-2024
*/

static int	ft_checkk(char **ptr, int index)
{
	if (!ptr || !(*ptr))
		return (0);
	while (ptr[index])
	{
		if (ft_strchr("<>|", ptr[index][0]) && ft_strlen(ptr[index]) >= 2)
		{
			if (ft_strlen(ptr[index]) > 2)
				return (0);
			if ((ptr[index][0] != ptr[index][1]) || !ptr[index + 1])
				return (0);
		}
		else if (index && ft_strchr("|<>", ptr[index][0]) && ft_strchr("|<>",
				ptr[index - 1][0]))
			return (0);
		else if (ft_strchr("|><", ptr[index][0]) && (!ptr[index + 1]
				|| ft_strchr("|><", ptr[index + 1][0])))
		{
			if (ptr[index][0] == '|' && ptr[index + 1] && ptr[index
				+ 1][0] != '|')
				return (1);
			return (0);
		}
		index++;
	}
	return (1);
}

/*
	@AUTHOR: Hicham BOUZID
	@DESC: Check if the syntax true or false
	@PROTOTYPE: char **syntax(char **ptr)
	DATE: 22-04-2024
*/
char	**syntax(char **ptr)
{
	if (!ft_checkk(ptr, 0))
	{
		ft_free(ft_strleen(ptr), ptr);
		ft_putstr_fd("bash: syntax error near unexpected token\n", 2);
		g_exit = 258;
		return (NULL);
	}
	return (ptr);
}
