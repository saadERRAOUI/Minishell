/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_minishell_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:24:26 by hibouzid          #+#    #+#             */
/*   Updated: 2024/04/21 22:58:51 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
	@AUTHOR: Hicham BOUZID
	@PROTOTYPE: char *expand_or_not(char *ptr)
	@DESC: util for expanding env variables
	@DATE:
*/
char	*expand_or_not(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '\"')
		{
			i++;
			while (ptr[i])
			{
				if (ptr[i] == '\"')
				{
					i++;
					break ;
				}
				i++;
			}
		}
		else if (ptr[i] == '\'')
		{
			i++;
			while (ptr[i])
			{
				if (ptr[i] == '\'')
				{
					i++;
					break ;
				}
				if (ptr[i] == '$')
					ptr[i] = DL;
				i++;
			}
		}
		else
			i++;
	}
	return (ptr);
}

/*
	@AUTHOR: Hicham BOUZID
	@PROTOTYPE: int	ft_strleen(char **ptr)
	@DESC: count lenght of an array tow dimention
	@DATE: 21-04-2024
*/

int	ft_strleen(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
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