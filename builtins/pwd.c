/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 06:09:11 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/29 23:37:11 by hibouzid         ###   ########.fr       */
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

int pwd(int ac, char **av)
{
	char BUFFER[PATH_MAX];
	if (ac == 1)
	{
		printf("%s\n", getcwd(BUFFER, sizeof(BUFFER)));
		return (0);
	}
	else
		ft_putstr_fd("pwd: too many arguments\n", 2);
	exit(1);
}
