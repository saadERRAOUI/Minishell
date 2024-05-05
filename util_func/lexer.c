/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:53:48 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/04 18:25:15 by hibouzid         ###   ########.fr       */
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

int	help(char *str, int *i, char *token)
{
	int	c;

	c = 0;
	*token = 0;
	if (str[*i] == '\"' || str[*i] == '\'')
	{
		c = str[*i];
		(*i)++;
		while (str[*i])
		{
			if (str[*i] != '\'' && str[*i] != '\"')
				*token = 1;
			if (str[*i] == c && token)
				break ;
			str[*i] = ft_check(str[*i]);
			(*i)++;
		}
		if (*i < (int)ft_strlen(str))
			(*i)++;
		return (1);
	}
	return (0);
}

char	*ft_convert_0(char *str)
{
	int		i;
	char	token;

	i = 0;
	while (str[i])
	{
		if (help(str, &i, &token))
			continue ;
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

/*
	@AUTHOR: hicham bouzid
	@PROTOTYPE: char	**add_dollar(char **ptr, t_env_v *env)
	@DESC: this function uset to replace env variable by
			by his value check if containe and call other func
	@DATE: 18-05-20240
*/

char	**add_dollar(char **ptr, t_env_v *env)
{
	int		i;
	int		token;
	char	*tmp;

	i = 0;
	while (ptr[i])
	{
		token = 0;
		if (ptr[i] && ft_strchr(ptr[i], '$'))
		{
			token = 1;
		}
		if (token && i && !ft_strcmp(ptr[i - 1], "<<"))
			token = 0;
		if (token)
		{
			tmp = ft_replace_dollar(ptr[i], env);
			free(ptr[i]);
			ptr[i] = tmp;
			i = 0;
		}
		i++;
	}
	return (ptr);
}
