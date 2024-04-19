/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_minishell_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:24:26 by hibouzid          #+#    #+#             */
/*   Updated: 2024/04/19 18:07:42 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static int	ft_bool(int singl, char token, int doubl)
{
	if ((token == '\"' && doubl % 2 == 0 && singl % 2 != 0 && singl != 1)
		|| (singl % 2 && singl != 1 && token != '\"'))
		return (0);
	if (token == '\"' && singl > 1 && singl % 2 != 0 && doubl % 2 == 0)
		return (0);
	if (token == '\'' && singl && singl % 2)
		return (0);
	if (token == '\"' && singl >= 1 && singl % 2 && doubl % 2 == 0)
		return (0);
	return (1);
}

int	ft_back(char *str, int index)
{
	int		tmp;
	char	token;
	int		singl;
	int		doubl;

	tmp = index;
	singl = 0;
	doubl = 0;
	token = 0;
	while (tmp >= 0)
	{
		if (str[tmp] == '\'')
		{
			token = str[tmp];
			singl++;
		}
		else if (str[tmp] == '\"')
		{
			token = str[tmp];
			doubl++;
		}
		tmp--;
	}
	return (ft_bool(singl, token, doubl));
}

/*
	@AUTHOR: Hicham BOUZID
	@PROTOTYPE: char *expand_or_not(char *ptr)
	@DESC: util for expanding env variables
	@DATE:
*/
char	*expand_or_not(char *ptr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ptr[i])
	{
		if (ptr[i] == '$')
		{
			if (i)
				j = i - 1;
			if (!ft_back(ptr, j))
				ptr[i] = DL;
		}
		i++;
	}
	return (ptr);
}
