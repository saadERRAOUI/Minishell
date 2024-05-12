/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 06:09:11 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/04 23:15:35 by serraoui         ###   ########.fr       */
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
	char	*buffer;

	buffer = malloc(sizeof(char) * 1024);
	buffer = getcwd(buffer, sizeof(buffer));
	if (!buffer && wds)
		printf("%s\n", wds->curr_wd);
	else
		printf("%s\n", getcwd(buffer, sizeof(buffer)));
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	return (0);
}
