/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 02:29:36 by serraoui          #+#    #+#             */
/*   Updated: 2024/05/02 22:29:14 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd  *parsexec(char **ps, int *pos, t_env_v *env)
{
	int			tok;
	int			argc;
	// char *t;
	char **tab;
	t_execcmd	*cmd;
    t_redircmd  *tmp;
	t_redircmd  *ret;

    (void)env;
	cmd = (t_execcmd *)execcmd();
    ret = NULL;
	argc = 0;
	parseredir(&ret, ps, pos);
	tok = get_token_type(ps[(*pos)]);
	while (ps[*pos] && tok && tok != '|')
	{
		if (tok != 'a')
			exit (-1); //! handle erro path
		cmd->argv[argc] = ps[(*pos)];
		argc++;
		if(argc >= MAXARGS)
			exit(1); 	//! too many args
		(*pos)++;
		parseredir(&ret, ps, pos);
		tok = get_token_type(ps[(*pos)]);
	}

		printf("i'm here\n");
	cmd->argv[argc] = NULL;
	if (cmd->argv)
	{
		cmd->envp = get_envp(env);
		// 	for (int i = 0; cmd->envp[i]; i++)
		// printf("%s\n", cmd->envp[i]);
		if (cmd->envp)
		{
			tab = ft_parce_env(cmd->envp);
			cmd->path = ft_cmd_valid(tab, cmd->argv);
			// ft_free(ft_strleen(tab), tab);
			free(tab);
		}
	}
	ft_print_tab(cmd->argv);
    printf("TEST %p\n", ret);
    if (ret && ret->type == 2)
    {
        tmp = ft_lstlast_(ret);
        tmp->cmd = (t_cmd *)cmd;
    }
    //!TO REMOVE TESTING PURPOSE
    if (!ret)
        return ((t_cmd *)cmd);
    // t_redircmd *_t;
    // _t = ret;
    // while (_t)
    // {
    //     printf("TYPE__type_____%i\n", ((t_redircmd *)_t)->type);
    //     printf("TYPE__cmd______%p\n", ((t_redircmd *)_t)->cmd);
    //     printf("TYPE__file_____%s\n", ((t_redircmd *)_t)->file);
    //     printf("TYPE__mode_____%i\n", ((t_redircmd *)_t)->mode);
    //     printf("TYPE__fd_______%i\n", ((t_redircmd *)_t)->fd);
    //     _t = _t->next;
    //     printf("===========================\n");
    // }
    //!TO REMOVE TESTING PURPOSE
	return ((t_cmd *)ret);
}

t_cmd  *parsepipe(char **ps, int *pos, t_env_v *env)
{
	t_cmd *cmd;

	cmd = parsexec(ps, pos, env);
	if(get_token_type(ps[(*pos)]) == '|')
	{
		(*pos)++;
		cmd = pipecmd(cmd, parsepipe(ps, pos, env));
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
	// printf("ret is :%c\n", (char)ret);
	return (ret);
}

void    parseredir(t_redircmd **red, char **ps, int *pos)
{
	int         tok;
    t_redircmd  *tmp;


	tok = get_token_type(ps[(*pos)]);
    while (tok == '>' || tok == '+' || tok == '<' || tok == '-')
    {
        if (tok != 'a' && tok != '|' && tok != '0' && get_token_type(ps[*pos + 1]) != 'a')
            exit(-1); //!to change to error "redirection file doesn't exist"
        switch(tok)
        {
            case '<':
                (*pos)++;
                tmp = redircmd(ps[(*pos)], O_RDONLY, 0);
                (*pos)++;
                ft_lstadd_back_(red, tmp);
                break;
            case '>':
                (*pos)++;
                tmp = redircmd(ps[(*pos)], O_RDONLY, 1);
                (*pos)++;

                //!TO REMOVE TESTING PURPOSE
                // printf("TMP__ %p\n", tmp);
                // printf("TMP__ %p\n", tmp->next);
                // printf("TMP__ %s\n", tmp->file);
                // if((*red)) {
                //     printf("TMP_TMP__ %p\n", (*red));
                //     printf("TMP_TMP__ %p\n", (*red)->next);
                //     printf("TMP_TMP__ %s\n", (*red)->file);
                // }
                //!TO REMOVE TESTING PURPOSE

                ft_lstadd_back_(red, tmp);
                break;
            case '+':
                (*pos)++;
                tmp = redircmd(ps[(*pos)], O_WRONLY | O_CREAT | O_TRUNC, 1);
                (*pos)++;
                ft_lstadd_back_(red, tmp);
                break;            
			case '-':
                (*pos)++;
                tmp = redircmd(ps[(*pos)], O_RDWR | O_CREAT, 0);
				//TODO : fork and call ft_here_doc();
                (*pos)++;
                ft_lstadd_back_(red, tmp);
                break;
        }
        tok = get_token_type(ps[(*pos)]);
    }
}
