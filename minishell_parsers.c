/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 02:29:36 by serraoui          #+#    #+#             */
/*   Updated: 2024/04/20 19:02:49 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd  *parsexec(char **ps, int *pos)
{
	int			tok; 
	int			argc;
	t_execcmd	*cmd;
	t_cmd		*ret;

	ret = execcmd();
	cmd = (t_execcmd *)ret;
	argc = 0;
	ret = parseredir(ret, ps, pos);
	tok = get_token_type(ps[(*pos)]);
	while (ps[*pos] && tok && tok != '|')
	{
		if (tok != 'a')
		{
			// printf("ERROR\n");
			exit (-1);
		}
		// printf("POS -> %i ; CON -> %s\n", *pos, ps[(*pos)]);
		cmd->argv[argc] = ps[(*pos)];
		argc++;
		if(argc >= MAXARGS)
			exit(1); 	//! too many args
		(*pos)++;
		ret = parseredir(ret, ps, pos);
		tok = get_token_type(ps[(*pos)]);
	}
	cmd->argv[argc] = NULL;
	ft_print_tab(cmd->argv);
	return (ret);
}

t_cmd  *parsepipe(char **ps, int *pos)
{
	t_cmd *cmd;

	cmd = parsexec(ps, pos);
	if(get_token_type(ps[(*pos)]) == '|')
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
		default :
			ret = 'a';
			break ;
	}
	return (ret);
}

t_cmd  *parseredir(t_cmd *cmd, char **ps, int *pos)
{
	int tok;

	// printf("POS_____ %i\n", *pos);
	tok = get_token_type(ps[(*pos)]);
	if (tok == 0 || tok == '|')
		return (cmd);
	if (tok != 'a' && tok != '|' && tok != '0' && get_token_type(ps[*pos + 1]) != 'a')
	{
		exit(-1); //!to change to error "redirection file doesn't exist"
	}
	switch(tok)
	{
		case '<':
			(*pos)++;
			cmd = redircmd(cmd, ps[(*pos)], O_RDONLY, 0);
			(*pos)++;
			return (parseredir(cmd, ps, pos));
			break;
		case '>':
			(*pos)++;
			cmd = redircmd(cmd, ps[(*pos)], O_WRONLY|O_CREAT, 1);
			(*pos)++;
			return (parseredir(cmd, ps, pos));
			break;
		case '+':
			(*pos)++;
			cmd = redircmd(cmd, ps[(*pos)], O_WRONLY|O_CREAT | O_TRUNC, 1);
			(*pos)++;
			return (parseredir(cmd, ps, pos));
			break;
	}
	return (cmd);
}
