/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_minishell_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:24:26 by hibouzid          #+#    #+#             */
/*   Updated: 2024/04/20 20:50:21 by hibouzid         ###   ########.fr       */
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
