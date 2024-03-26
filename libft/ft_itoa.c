/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:23:47 by hibouzid          #+#    #+#             */
/*   Updated: 2023/11/12 21:10:00 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_devis(long number)
{
	int	count;

	if (number < 10)
		return (1);
	count = 0;
	while (number >= 10)
	{
		number /= 10;
		count++;
	}
	return (count + 1);
}

static char	*ft_complet(long number, int count, char *b)
{
	while (number >= 10 && count)
	{
		b[count--] = number % 10 + 48;
		number /= 10;
	}
	b[count] = number + 48;
	return (b);
}

char	*ft_itoa(int n)
{
	long	number;
	int		sign;
	char	*b;
	int		count;

	sign = 1;
	count = 0;
	number = (long)n;
	if (number < 0)
	{
		number *= -1;
		sign *= -1;
		count += 1;
	}
	count += ft_devis(number);
	b = malloc(sizeof(char) * (count + 1));
	if (!b)
		return (NULL);
	b[count] = 0;
	count--;
	if (sign == -1)
		b[0] = '-';
	return (ft_complet(number, count, b));
}

// #include <stdio.h>

// int main()
// {
// 	printf("%s\n", ft_itoa(10));
// }
