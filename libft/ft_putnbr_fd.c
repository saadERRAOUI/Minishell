/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:50:25 by hibouzid          #+#    #+#             */
/*   Updated: 2023/11/15 11:57:33 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr(long number, int fd)
{
	if (number < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr(number * -1, fd);
	}
	else if (number < 10)
		ft_putchar_fd(number + 48, fd);
	else
	{
		ft_putnbr(number / 10, fd);
		ft_putnbr(number % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	number;

	if (fd < 0)
		return ;
	number = (long)n;
	ft_putnbr(number, fd);
}

// #include <stdio.h>

// int main()
// {
// 	ft_putnbr_fd(1555, 1);
// }
