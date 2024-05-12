/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:19:59 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/12 20:52:49 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup4(int *in, int *out, int *in_, int *out_)
{
	*in = dup(0);
	*out = dup(1);
	*in_ = dup(0);
	*out_ = dup(1);
}

void	ft_dup(t_redircmd *redir, int in, int out)
{
	if (redir->fd == 0)
	{
		if (g_exit == 1 && redir->mode == 514)
			return ;
		redir->fd = open(redir->file, O_RDONLY);
		if (redir->fd < 0)
			return (ft_putstr_fd("no such file of directory\n", 2));
		dup2(redir->fd, in);
	}
	if (redir->fd == 1 && redir->mode)
	{
		redir->fd = open(redir->file, O_CREAT | O_RDWR | O_APPEND, 0664);
		if (redir->fd < 0)
			return (ft_putstr_fd("problem in open function\n", 2));
		dup2(redir->fd, out);
	}
	else if (redir->fd == 1)
	{
		redir->fd = open(redir->file, O_CREAT | O_RDWR | O_TRUNC, 0664);
		if (redir->fd < 0)
			return (ft_putstr_fd("problem in open function\n", 2));
		dup2(redir->fd, out);
	}
	close(redir->fd);
}

int	get_token_type(char *s)
{
	int	ret;

	ret = '0';
	if (!s)
		return (ret);
	ret = (int)*s;
	if (*s == '|')
		ret = '|';
	else if (*s == '>')
	{
		if (*(s + 1) == '>')
			ret = '+';
	}
	else if (*s == '<')
	{
		if (*(s + 1) == '<')
			ret = '-';
	}
	else
		ret = 'a';
	return (ret);
}

t_redircmd	*here_doc_handler(t_env_v *env, int tok, int *pos, char **ps)
{
	t_redircmd	*tmp;
	char		*f;

	free(ps[*pos]);
	(*pos)++;
	tmp = redircmd(ps[(*pos)], O_RDWR | O_CREAT, 0);
	f = tmp->file;
	tmp->file = get_name();
	child_signal_def(2);
	if (fork() == 0)
	{
		child_signal_def(1);
		ft_here_doc(&tmp, env, f);
		exit(0);
	}
	wait(&tok);
	child_exit(tok);
	free(f);
	return (tmp);
}
