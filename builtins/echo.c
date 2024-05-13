/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:36:23 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/12 21:57:04 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	print_arg(int index, char **av, int ac)
{
	while (index < ac)
	{
		ft_putstr_fd(av[index], 1);
		if (index != ac - 1)
			ft_putstr_fd(" ", 1);
		index++;
	}
	return ;
}

int	only_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (1);
		i++;
	}
	if (!i)
		return (1);
	return (0);
}

static int	is_flag(char **ptr, int *i, int *token)
{
	int	j;

	while (ptr[*i])
	{
		j = 0;
		if (ptr[*i][j] == '-')
		{
			if (*i == 1)
			{
				if (!only_char((ptr[*i] + 1), 'n'))
				{
					*token = 1;
					(*i)++;
				}
			}
			else if (!only_char((ptr[*i] + 1), 'n'))
				(*i)++;
			else if (only_char((ptr[*i] + 1), 'n'))
				break ;
		}
		else
			break ;
	}
	return (*token);
}

int	echo(int ac, char **av)
{
	int	i;
	int	token;

	token = 0;
	if (ac >= 2)
	{
		i = 1;
		if (ft_strlen(av[1]) >= 2 && !ft_strncmp(av[i], "-n", 2))
			token = is_flag(av, &i, &token);
		print_arg(i, av, ac);
	}
	if (token == 0)
		ft_putstr_fd("\n", 1);
    g_exit = 0;
	return (0);
}
