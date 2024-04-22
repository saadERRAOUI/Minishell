/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 02:29:36 by serraoui          #+#    #+#             */
/*   Updated: 2024/04/21 23:40:51 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd  *parsexec(char **ps, int *pos)
{
	int			tok;
	int			argc;
	t_execcmd	*cmd;
	t_cmd		*ret;

	// char		*q;
	// char		*eq;
	ret = execcmd();
	cmd = (t_execcmd *)ret;
	argc = 0;
	ret = parseredir(ret, ps, pos);
	tok = get_token_type(ps[(*pos)]);
	while (ps[*pos] && tok && tok != '|')
	{
		// printf("tok --> %c\n", tok);
		if (tok != 'a')
		{
			exit (-1);	//! change to error path
		}
		printf("POS -> %i ; CON -> %s\n", *pos, ps[(*pos)]);
		cmd->argv[argc] = ps[(*pos)];
		// printf("_POS -> %i ; _CON -> %s\n", argc, cmd->argv[argc]);
		argc++;
		if (argc >= MAXARGS)
			exit(1); //! panic("too many args");
		(*pos)++;
		// printf("tok --> %c\n", tok);
		ret = parseredir(ret, ps, pos);
		// printf("_POS -> %i ; _CON -> %s\n", argc, cmd->argv[argc]);
		tok = get_token_type(ps[(*pos)]);
		// printf("__POS_ %i\n", *pos);
	}
	return (NULL);
}

t_cmd  *parsepipe(char **ps, int *pos)
{
	t_cmd	*cmd;

	cmd = parsexec(ps, pos);
	if (get_token_type(ps[(*pos)]) == '|')
	{
		(*pos)++;
		cmd = pipecmd(cmd, parsepipe(ps, pos));
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

t_cmd  *parseredir(t_cmd *cmd, char **ps, int *pos)
{
	int	tok;

	tok = get_token_type(ps[(*pos)]);
	if (tok != 'a' && tok != '|' && tok != '0' && get_token_type(ps[*pos
			+ 1]) != 'a')
	{
		exit(-1); //! to change to error "redirection file doesn't exist"
	}
	switch (tok)
	{
	// (*pos)++;
	case '<':
		(*pos)++;
		cmd = redircmd(cmd, ps[(*pos)], O_RDONLY, 0);
		break ;
	case '>':
		(*pos)++;
		cmd = redircmd(cmd, ps[(*pos)], O_WRONLY | O_CREAT, 1);
		break ;
	case '+': //* >>
		(*pos)++;
		cmd = redircmd(cmd, ps[(*pos)], O_WRONLY | O_CREAT | O_TRUNC, 1);
		break ;
	}
	return (cmd);
}
