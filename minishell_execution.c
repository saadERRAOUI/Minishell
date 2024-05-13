/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:48:44 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/13 00:46:57 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execut(t_cmd *cmd, t_env_v *env, t_pwd *wds)
{
	int	s;

	child_signal_def(2);
	if (ft_builtin_orch(((t_execcmd *)cmd)->argv, (t_execcmd *)cmd, &env, wds))
		return ;
	else
	{
		if (!((t_execcmd *)cmd)->argv || !((t_execcmd *)cmd)->argv[0])
			return ;
		else if (fork() == 0)
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
}

void	redir_cmd(t_cmd *cmd, t_env_v *env)
{
	int	in;
	int	out;
	int	in_;
	int	out_;

	dup4(&in, &out, &in_, &out_);
	while ((t_redircmd *)cmd)
	{
		ft_dup((t_redircmd *)cmd, in, out);
		if (((t_redircmd *)cmd)->fd == -1)
			return ;
		if (!((t_redircmd *)cmd)->next)
			break ;
		cmd = (t_cmd *)((t_redircmd *)cmd)->next;
	}
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
	ft_execut(((t_redircmd *)cmd)->cmd, env, NULL);
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

	if (!cmd)
		return ;
	if (cmd->type == 3)
		ft_pipe((t_pipecmd *)cmd, env);
	else if (cmd->type == 2)
		redir_cmd(cmd, env);
	else if (cmd->type == 1)
		ft_execut(cmd, env, wds);
	wait(&s);
	child_exit(s);
}
