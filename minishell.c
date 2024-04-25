/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:15:26 by serraoui          #+#    #+#             */
/*   Updated: 2024/04/25 14:55:55 by hibouzid         ###   ########.fr       */
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
/*
void procces(t_execcmd *cmd, int fd, int pip, int mode)
{
	char *path;
	if (mode == 0)
	{
		if (dup2(fd, 0) == -1 || dup2(pip, 1) == -1)
			ft_putstr_fd("error in dup function\n", 2);
		path =
	}
	else if (mode == 1)
	{
		if (dup2(pip, 0) == -1|| dup2(fd, 1) == -1)
			ft_putstr_fd("error in dup function\n", 2);
		if (execve(cmd->argv, ft_strjoin("/bin/", cmd->argv[0], 0)))
	}
}

char *get_path(v)
// void ft_run(t_cmd *cmd, int pip, t_env_v *env)
// {
// 	t_redircmd *cmd1;
// 	t_element *element;
// 	int i;

// 	i = 0;
// 	element = 0;
// 	if (cmd->type == 2)
// 	{
// 		cmd1 = (t_redircmd *)cmd;
// 		while (cmd1->next)
// 		{
// 			i = open(cmd1->file, cmd1->mode);
// 			if ((i < 0 && cmd1->fd == 0) || (i < 0))
// 			{
// 				if (i < 0 && cmd1->fd == 0)
// 					ft_putstr_fd("no such file or directory\n", 2);
// 				 else
// 					ft_putstr_fd("canno't open a file\n", 2);
// 			}
// 			else if (cmd1->cmd)
// 			{
// 				element = malloc(sizeof(t_element));
// 				element->path = get_path((t_execcmd *)cmd->argv, env);
// 			}
// 		}
// 	}
// }


void ft_pipe(t_cmd *left, t_cmd *right)
{
	pid_t pid;
	int pip[2];


	if (pipe(pip) == -1)
	{
		ft_putstr_fd("problem in pipe\n", 2);
		exit(-1);
	}
	pid = fork();
	if (pid == 0)
	{

	}
	else
	{

	}
}

// void ft_execution(t_cmd *cmd, t_env_v *env)
// {
// 	int tab[2];

// 	if (cmd->type == 3)
// 	{

// 	}
// 	else if (cmd->type == 2)
// 	{

// 	}
// }*/
/**
void exec_tree(t_cmd *cmd, t_env_v *env)
{
	if (cmd->type == 3)
	{
		// if (fork() == 0)
		// {
		// 	exec_tree(((t_pipecmd *)cmd)->left, env);
		// }
		// else if (((t_pipecmd *)cmd)->right->type , env) == 2)
		// {

		// }
	}
	else if (cmd->type == 2)
	{

	}
	else if (cmd->type == 1)
	{
		procces();
	}
}
*/

int	ft_run_shell(t_env_v *env)
{
	t_cmd	*cmd;
	char	*str;

	char	**ptr;
	int		pos;

	int i;

	(void)cmd;
	// pos = 0;
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
		// printf("--> %p\n", ptr);
		if (!ptr)
			continue ;
		ptr = ft_expand(ptr, env);
		// printf():
		// pos = 0;
		for (i = 0; ptr[i]; i++)
			printf("--> %s\n", ptr[i]);
		pos = 0;
		cmd = parsepipe(ptr, &pos, env);
		printf("TYPE CREATED TREE %i\n", cmd->type);
		printf("==================== \n");
		printf("====_PRINT_TREE_==== \n");
        printf("==================== \n");
        print_tree(cmd);
		//ft_execution(cmd, env);
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
	// ft_export(&env, ft_strdup("TEEEEEEST=test-"));
	// ft_export(&env, ft_strdup("saad=test"));
	// ft_export(&env, ft_strdup("TEEEEEEST+=saaad+saad+hachmi"));
	// ft_export(&env, ft_strdup("TEEEEEESTE+="));
	// ft_export(&env, NULL);
	ft_env(env);
	ft_run_shell(env);
}
