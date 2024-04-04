/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:15:26 by serraoui          #+#    #+#             */
/*   Updated: 2024/04/04 16:11:00 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	@AUTHOR	: Saad ERRAOUI
	@PROTO	: int	getToken(char **ps, char *es, char **q, char **eq);
	@DESC	: utility function that returns the next token (INT) in the parsed
		String.
	@DATE	: 24-03-2024
*/
int getToken(char **ps, char *es, char **q, char **eq)
{
	char *whitespaces;
	char *symbols;
	char *s;
	int ret;

	whitespaces = " \t\r\v\n";
	symbols = "<|>;&()";
	s = (*ps);
	while (s < es && ft_strchr(whitespaces, (*s)))
		s++;
	if (q)
		(*q) = s;
	ret = (*s);
	/* //TODO : MAKE THIS CODE IN A SEPERATE FUNC - START */
	switch (*s)
	{
	case 0:
		break;
	case '|':
	case '(':
	case ')':
	case '&':
	case ':':
		s++;
		break;
	case '>':
		s++;
		if (*s == '>')
		{
			ret = '+';
			s++;
		}
		break;
	case '<':
		s++;
		if (*s == '<')
		{
			ret = '-';
			s++;
		}
		break;
	default:
		ret = 'a';
		while (s < es && !ft_strchr(whitespaces, (*s)) && !ft_strchr(symbols, (*s)))
			s++;
		break;
	}
	/* //TODO : MAKE THIS CODE IN A SEPERATE FUNC - END */
	if (eq)
		(*eq) = s;
	while (s < es && ft_strchr(whitespaces, (*s)))
		s++;
	(*ps) = s;
	return (ret);
}

/*
	@AUTHOR	: Saad ERRAOUI
	@PROTO	: struct t_env_v	*env_init(char **env);
	@DESC	: utility function that initiate the env varibales by creating a linked list t_env_v
		an each node contains 1 env var defined by a (key, value) params.
	@DATE	: 25-03-2024
*/
t_env_v *env_init(char **env)
{
	t_env_v *envs;
	t_env_v *node;
	int i;
	char **s;

	if (!env)
		return (NULL);
	envs = NULL;
	i = 0;
	while (env[i])
	{
		node = (t_env_v *)malloc(sizeof(t_env_v));
		s = ft_split_2(env[i], '=');
		if (s) //! fix else case !
			(*node) = (t_env_v){s[0], s[1], NULL};
		ft_lstadd_back(&envs, node);
		free(s);
		i++;
	}
	return (envs);
}

/*
	@AUTHOR	: Saad ERRAOUI
	@PROTO	: int	peek(char **ps, char *es, char *toks);
	@DESC	: utility function that seeks the next none whitespace char
		and tells weither it exists and included in the toks chars.
	@DATE	: 30-03-2024
*/
int peek(char **ps, char *es, char *toks)
{
	char *s;

	s = *ps;
	while (s < es && ft_strchr(" \t\r\n\v", *s))
		s++;
	*ps = s;
	return (*s && ft_strchr(toks, *s));
}

/**
int main(int ac, char **av, char **env)
{
	t_env_v *envs;
	t_env_v *check;

	envs = env_init(env);
	// *TEST PURPOSE
	// printf("\n===============================================================\n\n");
	// while((*env)) {
	// 	printf("%s\n", (*env));
	// 	env++;
	// }
	if (!envs)
		return (0); //! hanle error if env unsetted
	// ft_env(envs);				   // env
	ft_export(&envs, " "); // export TEST=test
	ft_env(envs);
	// printf("\n== *SET* =============================================================\n\n");
	// ft_env(envs);
	// *im' fexed the leaks until here
	ft_unset(&envs, "LESS"); // unset TEST
	system("leaks a.out");
	// printf("\n== *UNSET* ===========================================================\n\n");
	// *TEST PURPOSE
	// check = envs;
	// while(check->next) {
	// 	printf("%s -> %s\n", check->key, check->value);
	// 	check = check->next;
	// }
}*/

//! TEST
// int main()
// {
// 	char *ps = "  >>sad|test";
// 	char *es = (char *)ps + 12;
// 	char *eq;
// 	char *q;
// 	int token = getToken(&ps, es, &q, &eq);
// 	printf("next token %i %c\n", token, token);

// 	token = getToken(&ps, es, &q, &eq);
// 	printf("next token %i %c\n", token, token);

// 	token = getToken(&ps, es, &q, &eq);
// 	printf("next token %i %c\n", token, token);
// 	return (0);
// }

int ft_run_shell(t_env_v *env)
{
	char *str;
	char **ptr;
	t_cmd *cmd;

	while (1)
	{
		str = readline("$ ");
		if (!str)
		{
			ft_free_stack(&env);
			exit(130);
		}
		if (!ft_handel_line(str))
			continue;
		ptr = ft_check_syntax(str);
		if (!ptr)
			continue;
		cmd = parsecmd(str);
		printf("TYPE CREATED TREE %i\n\n", cmd->type);
		// else
		free(str);
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
	t_env_v *env;

	(void)ac;
	(void)av;
	env = env_init(envp);
	if (!env)
		exit(-1);
	ft_run_shell(env);
}