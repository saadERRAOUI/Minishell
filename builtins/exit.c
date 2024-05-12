/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:14:04 by serraoui          #+#    #+#             */
/*   Updated: 2024/05/12 01:09:50 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/* **********************************************************************
	@__AUTHOR : ERRAOUI Saad
	@__PROTO  : int	ft_atoi_check(const char *, int *);
	@__DESC   : utility function that checks weither the const char *str
		is an intger or not, returns 1 if it is the case and 0 if not, and
		the number takes the int value in its content.
	@__DATE   : 10-12-2023
********************************************************************** */
int	ft_atoi_check(const char *str, int *number)
{
	int		i;
	int		sign;
	size_t	n;

	i = 0;
	sign = 1;
	(*number) = 0;
	n = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		n = n * 10 + str[i++] - '0';
	}
	if ((n > INT_MAX && sign == 1) || (n > 2147483648 && sign == -1))
		return (0);
	return ((*number) = n * sign, 1);
}

static void	exit_ndg(char *s)
{
	printf("exit: %s: numeric argument required\n", s);
	exit(255);
}

void	ft_exit(int ac, char **av)
{
	int		nbr;

	if (ac > 2)
	{
		g_exit = 1;
		printf("exit: too many arguments\n");
		return ;
	}
	else if (av[1] && ac == 2)
	{
		if (!ft_atoi_check(av[1], &nbr))
			exit_ndg(av[1]);
		g_exit = nbr;
	}
	exit(g_exit);
}
