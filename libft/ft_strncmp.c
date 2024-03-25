/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:26:17 by hibouzid          #+#    #+#             */
/*   Updated: 2023/11/13 11:37:26 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include<string.h>

// int main()
// {char *s  = 0;
// 	//printf("----> %d\n",ft_strncmp(NULL , "mnionvie", 0));

// 	printf("%d\n" ,ft_strncmp(0, "hjkujkn",0));
// }
