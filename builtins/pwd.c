/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 06:09:11 by hibouzid          #+#    #+#             */
/*   Updated: 2024/04/17 11:57:46 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
	@AUTHOR : hicham bouzid
	@PROTO	: int pwd();
	@DESC	: get the path of the current directory
				by use a syscall named getwcd
	@DATE	: 24-03-2024
*/

int	pwd(int ac, char **av)
{
	char	buffer[1024];

	(void)av;
	if (ac == 1)
	{
		printf("%s\n", getcwd(buffer, sizeof(buffer)));
		return (0);
	}
	else
		ft_putstr_fd("pwd: too many arguments\n", 2);
	exit(1);
}
