/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:50:58 by hibouzid          #+#    #+#             */
/*   Updated: 2023/11/03 18:36:06 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned long long	i;
	unsigned long long	f;

	i = 0;
	if (dstsize <= 0)
		return (ft_strlen(src));
	f = dstsize;
	while (i < f - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}

// #include<string.h>
// #include<stdio.h>
// int main()
// {
// 	char dst[5];
// 	char *src = "the 42  ";
// 	printf("size returned is == %d\n", (int)strlcpy(dst, src, -1));
// 	printf("the dest is  == %s\n", dst);
// }
