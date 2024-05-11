/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 02:29:36 by serraoui          #+#    #+#             */
/*   Updated: 2024/05/11 22:24:40 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parsexec(char **ps, int *pos, t_env_v *env)
{
	int			tok;
	int			argc;
	char		**tab;
	t_execcmd	*cmd;
	t_redircmd	*tmp;
	t_redircmd	*ret;

	(void)env;
	cmd = (t_execcmd *)execcmd();
	ret = NULL;
	argc = 0;
	parseredir(&ret, ps, pos, env);
	tok = get_token_type(ps[(*pos)]);
	while (ps[*pos] && tok && tok != '|')
	{
		if (tok != 'a')
			exit(-1);
		cmd->argv[argc] = ps[(*pos)];
		argc++;
		if (argc >= MAXARGS)
			exit(1);
		(*pos)++;
		parseredir(&ret, ps, pos, env);
		tok = get_token_type(ps[(*pos)]);
	}
	cmd->argv[argc] = NULL;
	if (cmd->argv)
	{
		// printf("=============----------\n");
		cmd->envp = get_envp(env);
		if (cmd->envp)
		{
			tab = ft_parce_env(cmd->envp);
			cmd->path = ft_cmd_valid(tab, cmd->argv);
			ft_free(ft_strleen(tab), tab);
		}
		else
			cmd->path = ft_cmd_valid(NULL, cmd->argv);
	}
	//ft_print_tab(cmd->argv);
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
        s_exit = 0; //TODO : test !!
	}
	return (cmd);
}

int	get_token_type(char *s)
{
	int	ret;

	ret = '0';
	if (!s)
		return (ret);
	ret = (int)*s;
	switch (*s)
	{
        case '|':
            break ;
        case '>':
            if (*(s + 1) == '>')
                ret = '+';
            break ;
        case '<':
            if (*(s + 1) == '<')
                ret = '-';
            break ;
        default:
            ret = 'a';
            break ;
	}
	return (ret);
}

void    parseredir(t_redircmd **red, char **ps, int *pos, t_env_v *env)
{
	int			tok;
	t_redircmd	*tmp;
	char *f;

	tok = get_token_type(ps[(*pos)]);
    while (tok == '>' || tok == '+' || tok == '<' || tok == '-')
    {
        if (tok != 'a' && tok != '|' && tok != '0' && get_token_type(ps[*pos + 1]) != 'a')
            exit(-1); //!to change to error "redirection file doesn't exist"
        switch(tok)
        {
            case '<':
				free(ps[*pos]);
                (*pos)++;
                tmp = redircmd(ps[(*pos)], O_RDONLY, 0);
                (*pos)++;
                ft_lstadd_back_(red, tmp);
                break;
            case '>':
				free(ps[*pos]);
                (*pos)++;
                tmp = redircmd(ps[(*pos)], O_RDONLY, 1);
                (*pos)++;
                ft_lstadd_back_(red, tmp);
                break;
            case '+':
				free(ps[*pos]);
                (*pos)++;
                tmp = redircmd(ps[(*pos)], O_WRONLY | O_CREAT | O_TRUNC, 1);
                (*pos)++;
                ft_lstadd_back_(red, tmp);
                break;
			case '-':
				free(ps[*pos]);
                (*pos)++;
                tmp = redircmd(ps[(*pos)], O_RDWR | O_CREAT, 0);
				f = tmp->file;
				tmp->file = get_name();
				tmp->token = 1;
				//TODO : fork and call ft_here_doc(); //done
                child_signal_def(2);
				if (fork() == 0)
                {
                    // signal(SIGQUIT, SIG_DFL);
                    // signal(SIGINT, SIG_DFL);
                    child_signal_def(1);
                    ft_here_doc(&tmp, env, f);
                }
				wait(&tok);
                child_exit(tok);
                (*pos)++;
                ft_lstadd_back_(red, tmp);
                break;
        }
        tok = get_token_type(ps[(*pos)]);
    }
}
