/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 02:29:36 by serraoui          #+#    #+#             */
/*   Updated: 2024/05/12 20:50:18 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_execcmd	*parse_exec_helper(t_redircmd **ret, char **ps, int *pos,
		t_env_v *env)
{
	t_execcmd	*cmd;
	int			tok;
	int			argc;

	argc = 0;
	cmd = (t_execcmd *)execcmd();
	parseredir(ret, ps, pos, env);
	tok = get_token_type(ps[(*pos)]);
	while (ps[*pos] && tok && tok != '|')
	{
		cmd->argv[argc] = ps[(*pos)];
		argc++;
		if (argc >= MAXARGS)
			exit(1);
		(*pos)++;
		parseredir(ret, ps, pos, env);
		tok = get_token_type(ps[(*pos)]);
	}
	cmd->argv[argc] = NULL;
	if (cmd->argv)
		cmd->envp = get_envp(env);
	return (cmd);
}

t_cmd	*parsexec(char **ps, int *pos, t_env_v *env)
{
	char		**tab;
	t_execcmd	*cmd;
	t_redircmd	*tmp;
	t_redircmd	*ret;

	ret = NULL;
	cmd = parse_exec_helper(&ret, ps, pos, env);
	if (cmd->envp)
	{
		tab = ft_parce_env(cmd->envp);
		cmd->path = ft_cmd_valid(tab, cmd->argv);
		ft_free(ft_strleen(tab), tab);
	}
	else
		cmd->path = ft_cmd_valid(NULL, cmd->argv);
	if (ret && ret->type == 2)
	{
		tmp = ft_lstlast_(ret);
		tmp->cmd = (t_cmd *)cmd;
	}
	if (!ret)
		return ((t_cmd *)cmd);
	return ((t_cmd *)ret);
}

t_cmd	*parsepipe(char **ps, int *pos, t_env_v *env)
{
	t_cmd	*cmd;

	cmd = parsexec(ps, pos, env);
	if (get_token_type(ps[(*pos)]) == '|')
	{
		free(ps[*pos]);
		(*pos)++;
		cmd = pipecmd(cmd, parsepipe(ps, pos, env));
		g_exit = 0;
	}
	return (cmd);
}

int	redir_helper(t_redircmd **red, int tok, int *pos, char **ps)
{
	t_redircmd	*tmp;

	free(ps[*pos]);
	(*pos)++;
	if (tok == '<')
	{
		tmp = redircmd(ps[(*pos)], O_RDONLY, 0);
		(*pos)++;
		ft_lstadd_back_(red, tmp);
	}
	else if (tok == '>')
	{
		tmp = redircmd(ps[(*pos)], O_RDONLY, 1);
		(*pos)++;
		ft_lstadd_back_(red, tmp);
	}
	else if (tok == '+')
	{
		tmp = redircmd(ps[(*pos)], O_WRONLY | O_CREAT | O_TRUNC, 1);
		(*pos)++;
		ft_lstadd_back_(red, tmp);
	}
	return (*pos);
}

void	parseredir(t_redircmd **red, char **ps, int *pos, t_env_v *env)
{
	int			tok;
	t_redircmd	*tmp;

	tok = get_token_type(ps[(*pos)]);
	while (tok == '>' || tok == '+' || tok == '<' || tok == '-')
	{
		if (tok != 'a' && tok != '|' && tok != '0' && get_token_type(ps[*pos
					+ 1]) != 'a')
			exit(-1);
		if (tok == '<' || tok == '>' || tok == '+')
			*pos = redir_helper(red, tok, pos, ps);
		else if (tok == '-')
		{
			tmp = here_doc_handler(env, tok, pos, ps);
			(*pos)++;
			ft_lstadd_back_(red, tmp);
			break ;
		}
		tok = get_token_type(ps[(*pos)]);
	}
}
