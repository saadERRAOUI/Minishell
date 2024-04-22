/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:15:26 by serraoui          #+#    #+#             */
/*   Updated: 2024/04/21 22:35:06 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	@AUTHOR	: Saad ERRAOUI
	@PROTO	: struct t_env_v	*env_init(char **env);
	@DESC	: utility function that initiate the env
	varibales by creating a linked list t_env_v
		an each node contains 1 env var defined by a (key, value) params.
	@DATE	: 25-03-2024
*/
t_env_v	*env_init(char **env)
{
	t_env_v	*envs;
	t_env_v	*node;
	int		i;
	char	**s;

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
int	peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(" \t\r\n\v", *s))
		s++;
	*ps = s;
	return (*s && ft_strchr(toks, *s));
}

/*
	@AUTHOR: Hicham BOUZID
	@PROTOTYPE: char **ft_expand(char **ptr, t_env_v *env)
	@DESC: this function check if the string containe an env variable
		and replacet at the last remove ' & "
	@DATE: 19-04-2024
*/
char	**ft_expand(char **ptr, t_env_v *env)
{
	int	i;
	int	j;

	i = 0;
	ptr = add_dollar(ptr, env);
	while (ptr[i])
	{
		j = 0;
		while (ptr[i][j])
		{
			if (ptr[i][j] == 7)
				ptr[i][j] = '$';
			j++;
		}
		i++;
	}
	i = 0;
	while (ptr[i])
	{
		ptr[i] = ft_shift(ptr[i]);
		i++;
	}
	return (ptr);
}

void ft_print_tab(char **s)
{
	int i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		if (s[i])
			printf("EXEC______  %s\n", s[i]);
		i++;
	}
}

static void print_tree(t_cmd *tree)
{
    printf("TREE____ %p\n", tree);
    if (tree && tree->type == 1)
    {
        printf("EXEC_NODE => %i\n", tree->type);
        printf("EXEC_NODE_argv\n");
        ft_print_tab(((t_execcmd *)tree)->argv);
        printf("-----------------------------\n");
    }
    else if (tree && tree->type == 2)
    {
        t_redircmd *_t;
        _t = (t_redircmd *)tree;
        printf("REDIR_NODE => %i\n", tree->type);
        while (_t)
        {
            printf("TYPE__type_____%i\n", ((t_redircmd *)_t)->type);
            printf("TYPE__cmd______%p\n", ((t_redircmd *)_t)->cmd);
            printf("TYPE__file_____%s\n", ((t_redircmd *)_t)->file);
            printf("TYPE__mode_____%i\n", ((t_redircmd *)_t)->mode);
            printf("TYPE__fd_______%i\n", ((t_redircmd *)_t)->fd);
            if (!_t->next)   
                print_tree(_t->cmd);
            _t = _t->next;
            printf("===========================\n");
        }
    }
    else if (tree && tree->type == 3)
    {
        printf("PIPE_NODE => %i\n", tree->type);
        printf("==================== LEFT\n");
        print_tree(((t_pipecmd *)tree)->left);
        printf("==================== RIGHT\n");
        print_tree(((t_pipecmd *)tree)->right);
    }
}

int	ft_run_shell(t_env_v *env)
{
	t_cmd	*cmd;
	char	*str;
	char	**ptr; 
	int		pos;

	(void)cmd;
	pos = 0;
	while (1)
	{
		str = readline("$ ");
		if (!str)
		{
			ft_free_stack(&env);
			exit(130);
		}
		if (!ft_handel_line(str))
			continue ;
		ptr = ft_check_syntax(str);
		if (!ptr)
			continue ;
		ptr = ft_expand(ptr, env);
		for (int i = 0; ptr[i]; i++)
			printf("--> %s\n", ptr[i]);
		pos = 0;
		cmd = parsepipe(ptr, &pos);
		printf("TYPE CREATED TREE %i\n", cmd->type);
		printf("==================== \n");
		printf("====_PRINT_TREE_==== \n");
        printf("==================== \n");
        print_tree(cmd);
        
		free(str);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_env_v	*env;

	(void)ac;
	(void)av;
	env = env_init(envp);
	if (!env)
		exit(-1);
	ft_run_shell(env);
}
