/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:37:01 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/05 15:47:46 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_free_execcmd(t_execcmd *cmd)
{
	ft_free(ft_strleen(cmd->argv), cmd->argv);
	free(cmd->path);
	ft_free(ft_strleen(cmd->envp), cmd->envp);
	free(cmd);
	cmd = NULL;
}

void ft_free_tree(t_cmd *cmd)
{
	if (cmd->type == 1)
		ft_free_execcmd((t_execcmd *)cmd);
	return ;
}