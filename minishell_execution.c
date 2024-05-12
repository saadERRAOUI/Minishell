/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:48:44 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/12 03:22:07 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execut(t_cmd *cmd, t_env_v *env, t_pwd *wds)
{
	int	s;

	(void)env;
	child_signal_def(2);
	if (ft_builtin_orch(((t_execcmd *)cmd)->argv, (t_execcmd *)cmd, &env, wds))
		return ;
	else
	{
		if (fork() == 0)
		{
			child_signal_def(1);
			if (execve((((t_execcmd *)cmd))->path, ((t_execcmd *)cmd)->argv,
					((t_execcmd *)cmd)->envp) == -1)
			{
				ft_putstr_fd("command not found\n", 2);
				exit(g_exit);
			}
		}
		else
		{
			wait(&s);
			child_exit(s);
		}
	}
	return ;
}

void	redir_cmd(t_cmd *cmd, t_env_v *env)
{
	t_redircmd	*redir;
	int			in;
	int			out;
	int			in_;
	int			out_;

	redir = (t_redircmd *)cmd;
	in = dup(0);
	out = dup(1);
	in_ = dup(0);
	out_ = dup(1);
	while (redir)
	{
		if (redir->fd == 0)
		{
			if (redir->mode == 514 && redir->token == 1)
				return ;
			redir->fd = open(redir->file, O_RDONLY);
			if (redir->fd < 0)
				ft_putstr_fd("no such file of directory\n", 2);
			if (dup2(redir->fd, in) == -1)
				printf("dup2\n");
		}
		else if (redir->fd == 1 && redir->mode)
		{
			redir->fd = open(redir->file, O_CREAT | O_RDWR | O_APPEND, 0664);
			if (redir->fd < 0)
				ft_putstr_fd("problem in open function\n", 2);
			if (dup2(redir->fd, out) == -1)
				printf("dup3\n");
		}
		else if (redir->fd == 1)
		{
			redir->fd = open(redir->file, O_CREAT | O_RDWR | O_TRUNC, 0664);
			if (redir->fd < 0)
				ft_putstr_fd("problem in open function\n", 2);
			if (dup2(redir->fd, out) == -1)
				printf("dup4\n");
		}
		close(redir->fd);
		if (!redir->next)
			break ;
		redir = redir->next;
	}
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
	ft_execut(redir->cmd, env, NULL);
	dup2(in_, 0);
	dup2(out_, 1);
	close(in_);
	close(out_);
}

static void	exec(int *pip, int fd, t_pipecmd *cmd, t_env_v *env)
{
	if (fd == 1)
	{
		child_signal_def(1);
		close(pip[0]);
		dup2(pip[1], 1);
		close(pip[1]);
		ft_execution(cmd->left, env, NULL);
		exit(0);
	}
	else if (fd == 0)
	{
		child_signal_def(1);
		close(pip[1]);
		dup2(pip[0], 0);
		close(pip[0]);
		ft_execution(cmd->right, env, NULL);
		exit(0);
	}
	return ;
}

void	ft_pipe(t_pipecmd *cmd, t_env_v *env)
{
	int	pip[2];
	int	s;

	child_signal_def(2);
	if (pipe(pip) == -1)
	{
		ft_putstr_fd("problem in pipe\n", 2);
		exit(EXIT_FAILURE);
	}
	if (fork() == 0)
		exec(pip, 1, cmd, env);
	if (fork() == 0)
		exec(pip, 0, cmd, env);
	close(pip[0]);
	close(pip[1]);
	wait(&s);
	child_exit(s);
}

void	ft_execution(t_cmd *cmd, t_env_v *env, t_pwd *wds)
{
	int	s;

	if (cmd->type == 3)
		ft_pipe((t_pipecmd *)cmd, env);
	else if (cmd->type == 2)
		redir_cmd(cmd, env);
	else if (cmd->type == 1)
		ft_execut(cmd, env, wds);
	wait(&s);
	child_exit(s);
}
