/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:22:40 by hibouzid          #+#    #+#             */
/*   Updated: 2024/04/03 17:52:24 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
	@AUTHER: hicham bouzid
	@DESC: join a char to an string
	@PROTOTYPE: char *ft_charjoin(char *str,
		char c)
	@DATE: 03-04-2024
*/

char *ft_charjoin(char *str, char c)
{
	int len;
	char *ptr;

	len = ft_strlen(str);
	ptr = malloc(sizeof(char) * (len + 2));
	if (!ptr)
		return (NULL);
	ptr[len + 1] = 0;
	len = 0;
	while (str[len])
	{
		ptr[len] = str[len];
		len++;
	}
	ptr[len] = c;
	free(str);
	return (ptr);
}

/*
	@AUTHER: hicham bouzid
	@DESC: check if chars in sym are syparde by space
	if not add space
	@PROTOTYPE: char *add_32(char *str, char *sym)
	@DATE: 03-04-2023
*/

char *add_32(char *str, char *sym)
{
	int i;
	char *ptr;

	ptr = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (i && ft_strchr(sym, str[i]) && str[i + 1] &&
			str[i + 1] != 32 && !ft_strchr(sym, str[i + 1]))
		{
			ptr = ft_charjoin(ptr, 32);
			ptr = ft_charjoin(ptr, str[i]);
			ptr = ft_charjoin(ptr, 32);
		}
		else
			ptr = ft_charjoin(ptr, str[i]);
		i++;
	}
	return (ptr);
}
