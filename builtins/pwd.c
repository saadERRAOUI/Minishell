/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 06:09:11 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/12 17:22:57 by serraoui         ###   ########.fr       */
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

int	pwd(t_pwd *wds)
{
	char	buffer[1024];

	getcwd(buffer, sizeof(buffer));
	if (!ft_strcmp(buffer, NULL) && wds)
		printf("%s\n", wds->curr_wd);
	else
		printf("%s\n", buffer);
	g_exit = 0;
	return (0);
}
