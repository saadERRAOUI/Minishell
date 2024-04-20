/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 02:29:36 by serraoui          #+#    #+#             */
/*   Updated: 2024/04/19 23:10:35 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parseline(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = NULL;
	(void)es;
	(void)ps;
	return (cmd);
}
t_cmd	*parsecmd(char *s)
{
	char	*es;
	t_cmd	*cmd;

	es = s + ft_strlen(s);
	cmd = parseline(&s, es);
	peek(&s, es, "");
	if (s != es)
	{
		printf("leftovers: %s\n", s);
		// panic("syntax"); //TODO : Add error handler function
	}
	// nulterminate(cmd); //!
	return (cmd);
}

// t_cmd  *parsexec(char **ps, char *es)
t_cmd	*parsexec(char **ps, int *pos)
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
			printf("ERROR\n");
			exit(-1); //! change to error path
		}
		//printf("ARGC___ %i\n", argc);
		cmd->argv[argc] = ps[(*pos)];
		argc++;
		if (argc >= MAXARGS)
			exit(1); //! panic("too many args");
		(*pos)++;
		// printf("tok --> %c\n", tok);
		ret = parseredir(ret, ps, pos);
		tok = get_token_type(ps[(*pos)]);
		// printf("__POS_ %i\n", *pos);
	}
	// cmd->argv[argc] = NULL;
	// printf("tok --> %c\n", tok);
	// printf("__HERE\n");
	/*
		ret = execcmd();
		cmd = (t_execcmd *)ret;
		argc = 0;
		ret = parseredir(ret, ps, es);
		while(!peek(ps, es, "|")){
			tok = getToken(ps, es, &q, &eq);
			if(tok == 0)
				break ;
			if(tok != 'a')
				// panic("syntax");
				exit(-1);
			cmd->argv[argc] = q;
			cmd->eargv[argc] = eq;
			argc++;
			if(argc >= MAXARGS)
				// panic("too many args");
				exit(1);
			ret = parseredir(ret, ps, es);
		}
		cmd->argv[argc] = 0;
		cmd->eargv[argc] = 0;
	*/
	return (ret);
}

// t_cmd  *parsepipe(char **ps, char *es)
t_cmd	*parsepipe(char **ps, int *pos)
{
	t_cmd	*cmd;

	cmd = parsexec(ps, pos);
	if (get_token_type(ps[(*pos)]) == '|')
	{
		// getToken(ps, es, 0, 0);
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

// t_cmd  *parseredir(t_cmd *cmd, char **ps, char *es)
t_cmd	*parseredir(t_cmd *cmd, char **ps, int *pos)
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
	//(*pos)++;
	// char *q, *eq;
	/*
		while(peek(ps, es, "<>"))
		{
			tok = getToken(ps, es, 0, 0);
			if(getToken(ps, es, &q, &eq) != 'a')
				// panic("missing file for redirection");
				exit(-1); //! to change error path
			switch(tok){
			case '<':
				cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
				break ;
			case '>':
				cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREAT, 1);
				break ;
			case '+':
				cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREAT | O_TRUNC, 1);
				break ;
			}
		}
	*/
	return (cmd);
}
