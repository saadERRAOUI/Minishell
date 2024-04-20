/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_constructors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:42:18 by serraoui          #+#    #+#             */
/*   Updated: 2024/04/05 03:58:26 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	@AUTHOR	: Saad ERRAOUI
	@PROTO	: t_cmd	*execcmd(void);
	@DESC	: utility function that initialize a t_execcmd instance with the correspondant params.
	@DATE	: 30-03-2024
*/
t_cmd	*execcmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(t_execcmd *));
	// TODO : Could be set to 0 "memset"
	ft_memset(cmd, 0, sizeof(t_execcmd *));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

/*
	@AUTHOR	: Saad ERRAOUI
	@PROTO	: t_cmd	*redircmd(t_cmd *subcmd, char *file, char *efile, int mode,
				int fd);
	@DESC	: utility function that initialize a t_redircmd instance with the correspondant params.
	@DATE	: 30-03-2024
*/
// t_cmd	*redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd)
t_cmd	*redircmd(t_cmd *subcmd, char *file, int mode, int fd)
{
	t_redircmd	*cmd;

	cmd = malloc(sizeof(t_redircmd *));
	ft_memset(cmd, 0, sizeof(t_redircmd *));
	cmd->type = REDIR;
	printf("_type %i\n", cmd->type);
	cmd->cmd = subcmd;
	cmd->file = file;
	// cmd->efile = efile;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}

/*
	@AUTHOR	: Saad ERRAOUI
	@PROTO	: t_cmd	*pipecmd(t_cmd *left, t_cmd	*right);
	@DESC	: utility function that initialize a t_pipecmd instance with the correspondant params.
	@DATE	: 30-03-2024
*/
t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = malloc(sizeof(t_pipecmd *));
	// memset(cmd, 0, sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(t_pipecmd *));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
