/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 02:29:36 by serraoui          #+#    #+#             */
/*   Updated: 2024/04/01 00:19:48 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parseline(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parsepipe(ps, es);
	return (cmd);
}

t_cmd  *parsecmd(char *s)
{
	char    *es;
	t_cmd	*cmd;

	es = s + ft_strlen(s);
	cmd = parseline(&s, es);
	peek(&s, es, "");
	if(s != es){
		printf("leftovers: %s\n", s);
		// panic("syntax"); //TODO : Add error handler function
	}
	// nulterminate(cmd); //!
	return cmd;
}

t_cmd  *parsexec(char **ps, char *es)
{
	char		*q;
	char		*eq;
	int			tok; 
	int			argc;
	t_execcmd	*cmd;
	t_cmd		*ret;

	ret = execcmd();
	cmd = (t_execcmd *)ret;
	argc = 0;
	ret = parseredir(ret, ps, es);
	while(!peek(ps, es, "|")){
		tok = getToken(ps, es, &q, &eq);
		if(tok == 0)
			break;
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
	return ret;
}

t_cmd  *parsepipe(char **ps, char *es)
{
	t_cmd *cmd;

	cmd = parsexec(ps, es);
	if(peek(ps, es, "|"))
	{
		getToken(ps, es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es));
	}
	return cmd;
}

t_cmd  *parseredir(t_cmd *cmd, char **ps, char *es)
{
	int tok;
	char *q, *eq;

	while(peek(ps, es, "<>"))
	{
		tok = getToken(ps, es, 0, 0);
		if(getToken(ps, es, &q, &eq) != 'a')
			// panic("missing file for redirection");
			exit(-1); //! to change error path 
		switch(tok){
		case '<':
			cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
			break;
		case '>':
			cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREAT, 1);
			break;
		case '+':  //* >>
			cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREAT | O_TRUNC, 1);
			break;
		}
	}
	return cmd;
}
