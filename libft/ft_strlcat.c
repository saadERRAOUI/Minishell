/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:18:27 by hibouzid          #+#    #+#             */
/*   Updated: 2023/11/04 11:13:43 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len_src;
	size_t	len_dst;

	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	i = ft_strlen(dst);
	if (dstsize == 0)
		return (len_src);
	if (dstsize <= len_dst)
		return (len_src + dstsize);
	j = 0;
	while (j < dstsize - len_dst - 1 && src[j])
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = 0;
	return (len_src + len_dst);
}

// #include <stdio.h>
// #include<string.h>

// int main()
// {
// 	char *src = "1337 is the best ";
// 	char tab[20] = "ben gruir11111";
// 	printf("the len of src----> %d\n", ft_strlen(src));
// 	printf("the len of dst----> %d\n", ft_strlen(tab));
// 	printf("the len returned is === %d\n", (int)strlcat(tab, "abcd", 7));
// 	// printf("my function returned is === %d\n", ft_strlcat(tab, src, 7));
// 	printf("-----> %s\n", tab);
// }
