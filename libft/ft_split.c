/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:05:34 by hibouzid          #+#    #+#             */
/*   Updated: 2024/04/17 11:51:02 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	is_charset(char *charset, char c)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (0);
		i++;
	}
	return (1);
}

static int	ft_count(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (is_charset(charset, str[0]))
		count++;
	while (str[i])
	{
		if (is_charset(charset, str[i]) == 0 && is_charset(charset, str[i
					- 1]) != 0)
			count++;
		i++;
	}
	if (!is_charset(charset, str[i - 1]))
		count--;
	return (count);
}

static char	**ft_alloc(char *str, char *charset, char **ptr, int e)
{
	int	i;
	int	j;

	j = -1;
	while (*str && j++ < e)
	{
		while (is_charset(charset, *str) == 0)
			str++;
		if (!*str)
			break ;
		i = 0;
		while (is_charset(charset, str[i]) && str[i])
			i++;
		ptr[j] = malloc(sizeof(char) * (i + 1));
		if (!ptr[j])
			return (NULL);
		ptr[j][i] = 0;
		i = 0;
		while (is_charset(charset, *str) && *str)
		{
			ptr[j][i++] = *str;
			str++;
		}
	}
	return (ptr);
}

char	**ft_split(char *str, char *charset)
{
	char	**ptr;
	int		i;

	if (!(*str))
	{
		ptr = malloc(sizeof(char *));
		ptr[0] = 0;
		return (ptr);
	}
	i = ft_count(str, charset);
	ptr = malloc(sizeof(char *) * (i + 1));
	if (!ptr)
		return (NULL);
	ptr[i] = NULL;
	ft_alloc(str, charset, ptr, i);
	return (ptr);
}
