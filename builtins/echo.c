/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:36:23 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/23 18:14:13 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void print_arg(int index, char **av, int ac)
{
	while (index < ac)
	{
		ft_putstr_fd(av[index], 1);
		if (index != ac - 1)
			ft_putstr_fd(" ", 1);
		index++;
	}
	return;
}

int echo(int ac, char **av)
{
	int i;

	if (ac >= 2)
	{
		if (!ft_strcmp(av[1], "-n"))
		{
			i = 2;
			print_arg(i, av, ac);
			return (0);
		}
		else
		{
			print_arg(1, av, ac);
			ft_putstr_fd("\n", 1);
		}
	}
	return (0);
}
