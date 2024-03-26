/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:10:14 by hibouzid          #+#    #+#             */
/*   Updated: 2023/11/15 11:50:55 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*srcs;

	i = 0;
	if (dst == src)
		return (dst);
	dest = (unsigned char *)dst;
	srcs = (unsigned char *)src;
	if (!dst && !src)
		return (dst);
	while (i < n)
	{
		dest[i] = srcs[i];
		i++;
	}
	return (dst);
}
