/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:40:35 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/12 01:45:37 by hibouzid         ###   ########.fr       */
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
		if (s)
			(*node) = (t_env_v){s[0], s[1], NULL};
		ft_lstadd_back(&envs, node);
		free(s);
		i++;
	}
	return (envs);
}

int	ft_builtin_orch(char **argv, t_execcmd *cmd, t_env_v **env, t_pwd *wds)
{
	if (!argv || !argv[0])
		return (0);
	if (!ft_strcmp("echo", argv[0]))
		return (echo(ft_strleen(cmd->argv), cmd->argv), 1);
	else if (!ft_strcmp("cd", argv[0]))
		return (cd(cmd->argv, wds), 1);
	else if (!ft_strcmp("pwd", argv[0]))
		return (pwd(wds), 1);
	else if (!ft_strcmp("export", argv[0]))
		return (ft_export(env, cmd->argv), 1);
	else if (!ft_strcmp("unset", argv[0]))
		return (ft_unset(env, cmd->argv), 1);
	else if (!ft_strcmp("env", argv[0]))
		return (ft_env((*env)), 1);
	else if (!ft_strcmp("exit", argv[0]))
		return (ft_exit(ft_strleen(cmd->argv), cmd->argv), 1);
	return (0);
}

/*
	@AUTHOR: BOUZID Hicham
	@DESC: get a random name for a temporary file
		for a here_doc
	@DATE: 02-05-2024
*/
char	*get_name(void)
{
	char	*name;
	char	c;
	char	*tmp;
	int		fd;
	int		i;

	i = 0;
	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		ft_putstr_fd("bad file descriptor : open ", 2);
	name = ft_strdup("          ");
	while (i < 10)
	{
		if (read(fd, &c, 1) == -1)
			ft_putstr_fd("error in read function\n", 2);
		if (ft_isalnum(c))
			name[i++] = c;
	}
	close(fd);
	tmp = name;
	name = ft_strjoin(ft_strdup("/tmp/"), name);
	free(tmp);
	return (name);
}
