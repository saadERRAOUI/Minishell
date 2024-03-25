/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:24:35 by hibouzid          #+#    #+#             */
/*   Updated: 2023/11/02 12:07:14 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*sr;

	i = 0;
	sr = (unsigned char *)s;
	while (i < n)
	{
		if (sr[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
