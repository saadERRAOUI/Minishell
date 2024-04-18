/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_minishell_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:24:26 by hibouzid          #+#    #+#             */
/*   Updated: 2024/04/18 22:23:29 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"


int ft_back(char *str, int index)
{
	int tmp;
	char token;
	int singl;
	int doubl;
	
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
	// if (token == '\"' && doubl % 2 == 0 && singl % 2 != 0)
	if (token == '\"' && doubl % 2 == 0 && singl % 2 != 0 && singl != 1)
	{
		printf("----\n");
		return (0);
	}
	if (singl % 2 != 0 && singl != 1 && token != '\"')
	{
		printf("====\n");
		return (0);
	}
	return (1);
}

char *expand_or_not(char *ptr)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (ptr[i])
	{
			if (ptr[i] == '$')
			{
				if (i)
					j = i - 1;
				if (!ft_back(ptr , j))
				ptr[i] = DL;
			}
			i++;
	}
	return (ptr);
}
