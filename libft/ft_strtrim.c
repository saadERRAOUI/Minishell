/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:59:25 by hibouzid          #+#    #+#             */
/*   Updated: 2023/11/12 21:25:53 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_check(char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = 0;
	if (!set || !s1)
		return (NULL);
	if (!*s1)
		return (ft_strdup(""));
	while (ft_check((char *)set, s1[start]) == 1)
		start++;
	end = ft_strlen(s1) - 1;
	while (ft_check((char *)set, s1[end]) == 1 && end >= 0 && end != start)
		end--;
	if (end < start)
		return (ft_strdup(""));
	str = malloc(sizeof(char) * (2 + end - start));
	if (!str)
		return (NULL);
	while (s1[start] && start <= end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}
