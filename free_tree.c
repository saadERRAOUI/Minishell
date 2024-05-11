/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:37:01 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/11 16:23:35 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_free_execcmd(t_execcmd *cmd)
{
	printf("--------> %s\n", cmd->argv[1]);
	ft_free(ft_strleen(cmd->argv), cmd->argv);
	free(cmd->path);
	if (cmd->envp)
		ft_free(ft_strleen(cmd->envp), cmd->envp);
	free(cmd);
	cmd = NULL;
}

void ft_free_redir(t_redircmd *cmd)
{
	t_redircmd *tmp;

	while (cmd)
	{
		if (cmd->cmd)
			ft_free_execcmd((t_execcmd *)cmd->cmd);
		if (cmd->mode && !cmd->fd)
		{
			if (unlink(cmd->file) == -1)
				ft_putstr_fd("problem in unlink function\n", 2);
		}
		free(cmd->file);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void ft_free_pipe(t_cmd *cmd)
{
	t_cmd *tmp;

	tmp = cmd;
	if (((t_pipecmd *)cmd)->left)
		ft_free_tree(((t_pipecmd *)cmd)->left);
	if (((t_pipecmd *)cmd)->right->type == 3)
	{
		cmd = ((t_pipecmd *)cmd)->right;
		free(tmp);
		ft_free_pipe(cmd);
	}
	else if (((t_pipecmd *)cmd)->right->type != 3)
	{
		ft_free_tree(((t_pipecmd *)cmd)->right);
		free(tmp);
	}
}

void ft_free_tree(t_cmd *cmd)
{
	if (cmd->type == 1)
		ft_free_execcmd((t_execcmd *)cmd);
	if (cmd->type == 2)
		ft_free_redir((t_redircmd *)cmd);
	else if (cmd->type == 3)
		ft_free_pipe(cmd);
	return ;
}
