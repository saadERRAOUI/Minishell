/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:22:40 by hibouzid          #+#    #+#             */
/*   Updated: 2024/04/04 16:13:03 by hibouzid         ###   ########.fr       */
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
		if (ft_strchr(sym, str[i]) && str[i + 1] &&
			str[i + 1] != 32 && i - 1 >= 0 && str[i - 1] != '\\')
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

/*
	@AUTHOR: hicham bouzid
	@DESC: remove " and ' by shif the string
	@PROTOTYPE: char *ft_shift(char *ptr)
	@DATE: 04-04-2024
*/

char *ft_shift(char *ptr)
{
	int i;
	int j;
	char c;

	i = 0;
	j = 0;
	char *str = ft_strdup(ptr);
	while (ptr[i])
	{
		if (ptr[i] == '\'' || ptr[i] == '\"')
		{
			c = ptr[i];
			i++;
			while (ptr[i] != c && ptr[i])
				str[j++] = ptr[i++];
		}
		else
			str[j++] = ptr[i++];
	}
	str[j] = 0;
	free(ptr);
	return (str);
}

// !todo add function to check if the syntax true or not
char **ft_check_syntax(char *str)
{
	char **ptr;
	int i;

	str = ft_convert_0(str);
	str = add_32(str, "|<>");
	ptr = ft_split(str, " \t\v\r\f");
	ptr = undo(ptr);
	i = 0;
	while (ptr[i])
	{
		ptr[i] = ft_shift(ptr[i]);
		i++;
	}
	return (ptr);
}