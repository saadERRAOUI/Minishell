/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:04:52 by hibouzid          #+#    #+#             */
/*   Updated: 2023/11/07 19:10:18 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *)b;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

// #include <stdio.h>
// int main()
// {
// 	int tab[] = {1, 5,6};
// 	void *ptr ;
// 	int i;

// 	ptr  = ft_memset((void *)tab, 4, 12);
// 	for (i =  0; i < 3; i++)
// 	printf("%d\n", tab[i]);
// }
