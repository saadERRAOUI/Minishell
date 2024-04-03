/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:16:07 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/31 23:12:19 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(unsigned char *dst, unsigned char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (dst == src)
			return (0);
		i++;
		src++;
	}
	return (1);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int				f;
	unsigned char	*dest;
	unsigned char	*srcs;

	dest = (unsigned char *)dst;
	srcs = (unsigned char *)src;
	if (!dst && !src)
		return (0);
	if (ft_check(dest, srcs, len) == 0)
	{
		f = (int)len - 1;
		while (f >= 0)
		{
			dest[f] = srcs[f];
			f--;
		}
		return (dst);
	}
	return (ft_memcpy(dst, src, len));
}
/**
#include <stdio.h>
#include <string.h>

// int	main(void)
{
	printf("function system ==== %s\n", (char *)memmove(((void *)0),
			((void *)0), 5));
	printf("my function  ==== %s\n", (char *)ft_memmove(((void *)0),
			((void *)0), 5));
}
*/
