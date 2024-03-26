/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:14:31 by hibouzid          #+#    #+#             */
/*   Updated: 2023/11/17 10:46:05 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*ndl;
	char	*hst;
	size_t	i;
	size_t	j;

	ndl = (char *)needle;
	hst = (char *)haystack;
	if (!*ndl)
		return (hst);
	i = 0;
	while (hst[i] && i < len && len >= ft_strlen(ndl))
	{
		j = 0;
		if (hst[i] == ndl[j])
		{
			while ((ndl[j] == hst[i + j]) && ndl[j] && hst[j + i] && i
				+ j < len)
				j++;
			if (j == ft_strlen(ndl))
				return (hst + i);
		}
		i++;
	}
	return (0);
}
