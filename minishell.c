/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:15:26 by serraoui          #+#    #+#             */
/*   Updated: 2024/05/12 02:09:52 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tab(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		if (s[i])
			printf("EXEC______  %s\n", s[i]);
		i++;
	}
}

/*
static void	print_tree(t_cmd *tree)
{
		t_redircmd *_t;

	printf("TREE____ %p\n", tree);
	if (tree && tree->type == 1)
	{
		printf("EXEC_NODE => %i\n", tree->type);
		printf("EXEC_NODE_argv\n");
		ft_print_tab(((t_execcmd *)tree)->argv);
		if (((t_execcmd *)tree)->path)
		{
			printf("-------%d--------\n",
				(int)ft_strleen(((t_execcmd *)tree)->argv));
			printf("path: %s\n", ((t_execcmd *)tree)->path);
		}
	}
	else if (tree && tree->type == 2)
	{
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
*/

void	ft_here_doc(t_redircmd **cmd, t_env_v *env, char *delimeter)
{
	char	*str;
	char	*tm;

	(*cmd)->fd = open((*cmd)->file, O_CREAT | O_RDWR, 0777);
	if ((*cmd)->fd < 0)
		ft_putstr_fd("Error in open function\n", 2);
	while (1)
	{
		str = readline("> ");
		if (!str)
			printf("DELIM_NOT_DONE\n");
		if (!ft_strcmp(str, delimeter))
		{
			free(str);
			break ;
		}
		if (str && ft_strchr(str, '$'))
		{
			tm = str;
			str = ft_replace_dollar(str, env);
			free(tm);
		}
		ft_putstr_fd(str, (*cmd)->fd);
		ft_putstr_fd("\n", (*cmd)->fd);
		free(str);
	}
	close((*cmd)->fd);
	(*cmd)->fd = 0;
	(*cmd)->token = 0;
}

static void	ft_here(void)
{
	return ;
}

int	ft_run_shell(t_env_v *env)
{
	t_cmd	*cmd;
	char	*str;
	char	buffer[1024];
	char	**ptr;
	int		pos;
	t_pwd	*wds;

	wds = malloc(sizeof(t_pwd));
	getcwd(buffer, sizeof(buffer));
	(*wds) = (t_pwd){NULL, ft_strdup(buffer)};
	while (1)
	{
		child_signal_def(0);
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
		{
			free(str);
			continue ;
		}
		ptr = ft_expand(ptr, env);
		pos = 0;
		cmd = parsepipe(ptr, &pos, env);
		ft_execution(cmd, env, wds);
		ft_free_tree(cmd);
		free(ptr);
		free(str);
		ft_here();
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_env_v	*env;

	(void)ac;
	(void)av;
	env = env_init(envp);
	ft_run_shell(env);
}
