/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:05:34 by hibouzid          #+#    #+#             */
/*   Updated: 2023/11/12 21:17:55 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	is_separator(char s, char c)
{
	return ((c == s));
}

static int	ft_count(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!is_separator(s[0], c))
	{
		count++;
		i++;
	}
	while (s[i])
	{
		if (is_separator(s[i], c) && s[i + 1] && !is_separator(s[i + 1], c))
			count++;
		i++;
	}
	return (count);
}

static char	**ft_free(int index, char **ptr)
{
	while (index >= 0)
	{
		free(ptr[index]);
		index--;
	}
	free(ptr);
	return (0);
}

static char	**ft_alloc(char **ptr, const char *s, char c, int e)
{
	int	i;
	int	j;
	int	f;

	i = 0;
	j = 0;
	while (s[i] && j != e)
	{
		while (is_separator(s[i], c) && s[i])
			i++;
		f = i;
		if (!s[f])
			break ;
		while (!is_separator(s[f], c) && s[f])
			f++;
		ptr[j] = malloc(sizeof(char) * (1 + f - i));
		if (!ptr[j])
			return (ft_free(j - 1, ptr));
		f = 0;
		while (s[i] && !is_separator(s[i], c))
			ptr[j][f++] = s[i++];
		ptr[j][f] = 0;
		j++;
	}
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		count;

	if (!s || !*s)
	{
		ptr = malloc(sizeof(char *));
		if (!ptr)
			return (NULL);
		ptr[0] = 0;
		return (ptr);
	}
	count = ft_count(s, c);
	ptr = malloc(sizeof(char *) * (count + 1));
	if (!ptr)
		return (NULL);
	ptr[count] = 0;
	return (ft_alloc(ptr, s, c, count));
}
