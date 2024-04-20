/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:53:48 by hibouzid          #+#    #+#             */
/*   Updated: 2024/04/19 18:17:48 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
	@AUTOR: hicham bouzid
	@DESC: function remplace a symbols if inside a "" or ''
		by imprintibale charchter
	@PROTOTYPE: char *ft_convert_0(char *str)
	@DATE: 04-04-2024
*/

static char	ft_check(char c)
{
	if (c == '|')
		c = PIPE;
	else if (c == '<')
		c = LEFT;
	else if (c == '>')
		c = RIGHT;
	else if (c == 32 || (c >= 9 && c <= 13))
		c = SPACE;
	return (c);
}

char	*ft_convert_0(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		c = 0;
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i])
			{
				str[i] = ft_check(str[i]);
				i++;
			}
			if (i < (int)ft_strlen(str))
				i++;
		}
		else
			i++;
	}
	return (str);
}

/*
	@AUTHOR: hicham bouzid
	@DESC: function undo changes
	@PROTOTYPE: char **undo(char **ptr)
	@DATE: 04-04-2024
*/

char	**undo(char **ptr)
{
	int	i;
	int	j;

	i = 0;
	while (ptr[i])
	{
		j = 0;
		while (ptr[i][j])
		{
			if (ptr[i][j] == PIPE)
				ptr[i][j] = '|';
			else if (ptr[i][j] == RIGHT)
				ptr[i][j] = '>';
			else if (ptr[i][j] == LEFT)
				ptr[i][j] = '<';
			else if (ptr[i][j] == SPACE)
				ptr[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (ptr);
}
