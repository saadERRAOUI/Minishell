/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:53:48 by hibouzid          #+#    #+#             */
/*   Updated: 2024/04/04 14:55:07 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
	@AUTER: hicham bouzid
	@DESC: function remplace a symbols if inside a "" or ''
		by imprintibale charchter
	@PROTOTYPE: char *ft_convert_0(char *str)
	@DATE: 04-04-2024
*/

char *ft_convert_0(char *str)
{
	int i;
	char c;

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
				if (str[i] == '|')
					str[i] = PIPE;
				else if (str[i] == '<')
					str[i] = LEFT;
				else if (str[i] == '>')
					str[i] = RIGHT;
				else if (str[i] == 32 || (str[i] >= 9  && str[i] <= 13))
					str[i] = SPACE;
				i++;
			}
		}
		else
			i++;
	}
	return (str);
}

/*
	@AUTHER: hicham bouzid
	@DESC: function undo changes
	@PROTOTYPE: char **undo(char **ptr)
	@DATE: 04-04-2024
*/

char **undo(char **ptr)
{
	int i;
	int j;

	i = 0;
	while (ptr[i])
	{
		j = 0;
		while (ptr[i][j])
		{
			if (ptr[i] == PIPE)
				ptr[i] = '|';
			else if (ptr[i] == RIGHT)
				ptr[i] = '>';
			else if (ptr[i] == LEFT)
				ptr[i] = '<';
			else if (ptr[i] == SPACE)
				ptr[i] = ' ';
			j++;
		}
		i++;
	}	
	return (ptr);
}
