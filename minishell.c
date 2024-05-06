/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:15:26 by serraoui          #+#    #+#             */
/*   Updated: 2024/05/06 15:39:14 by hibouzid         ###   ########.fr       */
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
void ft_execut(t_cmd *cmd, t_env_v *env, t_pwd *wds);
void ft_execution(t_cmd *cmd, t_env_v *env, t_pwd *wds);

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

/**
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
			printf("path: %s\n", ((t_execcmd *)tree)->path);
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

void	ft_procces(t_cmd *cmd, int mode, int *pip, t_env_v *env)
{
	t_pipecmd	*cd;

	cd = (t_pipecmd *)cmd;
	if (mode == 0)
	{
		close(pip[0]);
		dup2(pip[1], 1);
		close(pip[1]);
		ft_execution(cd->left, env, NULL);
	}
	else if (mode == 1)
	{
		close(pip[0]);
		dup2(pip[1], 1);
		close(pip[1]);
		ft_execution(cd->right, env, NULL);
	}
	close(0);
	close(1);
	return ;
}

void	ft_pipe(t_pipecmd *cmd, t_env_v *env)
{
	pid_t	pid;
	pid_t	pid1;
	int		pip[2];

	if (pipe(pip) == -1)
	{
		ft_putstr_fd("problem in pipe\n", 2);
		exit(-1);
	}
	pid = fork();
	if (pid < 0)
		ft_putstr_fd("error in fork child 1\n", 2);
	if (pid == 0)
	{
		close(pip[0]);
		dup2(pip[1], 1);
		close(pip[1]);
		ft_execution(cmd->left, env, NULL);
	}
	pid1 = fork();
	if (pid1 < 0)
		ft_putstr_fd("error in fork child 2\n", 2);
	if (pid1 == 0)
	{
		close(pip[1]);
		dup2(pip[0], 0);
		close(pip[0]);
		ft_execution(cmd->right, env, NULL);
	}
	close(pip[0]);
	close(pip[1]);
	wait(0);
	// wait(0);
}

int ft_builtin_orch(char **argv, t_execcmd *cmd, t_env_v **env, t_pwd *wds)
{
	if (!argv || !argv[0])
        return (0);
	
    if (!ft_strcmp("echo", argv[0])) //echo
        return (echo(ft_strleen(cmd->argv), cmd->argv), 1);
    else if (!ft_strcmp("cd", argv[0]))
        return (cd(cmd->argv, wds), 1);
    else if (!ft_strcmp("pwd", argv[0]))
        return (pwd(wds), 1);
    else if (!ft_strcmp("export", argv[0]))
        return (ft_export(env, cmd->argv[1]), 1);
    else if (!ft_strcmp("unset", argv[0]))
        return (ft_unset(env, cmd->argv[1]), 1);
    else if (!ft_strcmp("env", argv[0]))
        return (ft_env((*env)), 1);
    else if (!ft_strcmp("exit", argv[0]))
        return (ft_exit(ft_strleen(cmd->argv), cmd->argv), 1);
	return (0);
}

void ft_execut(t_cmd *cmd, t_env_v *env, t_pwd *wds)
{
	t_execcmd *cd;
	(void)env;

	cd = (t_execcmd *)cmd;
	if (ft_builtin_orch(cd->argv, cd, &env, wds))
		return ;
	if (!cd->path)
	{
		ft_putstr_fd("command not found\n", 2);
		return ;
	}
	else if (fork() == 0)
	{
		if (execve(cd->path, cd->argv, cd->envp) == -1)
			ft_putstr_fd("error happen in execve\n", 2);
		wait(0);
	}
	return ;
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

void	ft_here_doc(t_redircmd **cmd, t_env_v *env)
{
	char	*tmp;
	char	*str;
	char	*tm;

	// int f;
	tmp = get_name();
	printf("--->%s\n", tmp);
	(*cmd)->fd = open(tmp, O_CREAT | O_RDWR, 0777);
	if ((*cmd)->fd < 0)
		ft_putstr_fd("Error in open function\n", 2);
	while (1)
	{
		str = readline("> ");
		if (!ft_strcmp(str, (*cmd)->file))
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
	(*cmd)->fd = open(tmp, O_RDONLY);
	free((*cmd)->file);
	(*cmd)->file = tmp;
	if ((*cmd)->fd < 0)
		ft_putstr_fd("error in  open function \n", 2);
}

void	redir_cmd(t_cmd *cmd, t_env_v *env)
{
	t_redircmd	*redir;
	int			in;
	int			out;

	// int token;
	redir = (t_redircmd *)cmd;
	in = dup(0);
	out = dup(1);
	int in_ = dup(0);
	int out_ = dup(1);
	while (redir)
	{
		// if (redir->fd == 0 && redir->mode)
		// {
		// 	ft_here_doc(&redir, env);
		// 	dup2(redir->fd, in);
		// }
		if (redir->fd == 0)
		{
			redir->fd = open(redir->file, O_CREAT | O_RDONLY);
			if (redir->fd < 0)
				printf("erro");
			dup2(redir->fd, in);
		}
		else if (redir->fd == 1 && redir->mode)
		{
			redir->fd = open(redir->file, O_CREAT | O_RDWR | O_APPEND, 0664);
			if (redir->fd < 0)
				ft_putstr_fd("problem in open function\n", 2);
			dup2(redir->fd, out);
		}
		else if (redir->fd == 1)
		{
			redir->fd = open(redir->file, O_CREAT | O_RDWR | O_TRUNC, 0664);
			if (redir->fd < 0)
				ft_putstr_fd("problem in open function\n", 2);
			dup2(redir->fd, out);
		}
		close(redir->fd);
		if (!redir->next)
			break ;
		redir = redir->next;
	}
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
	ft_execut(redir->cmd, env, NULL);
	dup2(in_, 0);
	dup2(out_, 1);
	close(in_);
	close(out_);
}

void ft_execution(t_cmd *cmd, t_env_v *env, t_pwd *wds)
{
	if (cmd->type == 3)
		ft_pipe((t_pipecmd *)cmd, env);
	else if (cmd->type == 2)
		redir_cmd(cmd, env);
	else if (cmd->type == 1)
		ft_execut(cmd, env, wds);
	// wait(0);
}

int	ft_run_shell(t_env_v *env)
{
	t_cmd	*cmd;
	char	*str;
   char    buffer[1024];
	char	**ptr;
	int		pos;
	// int     i;
    t_pwd   *wds;

    wds = malloc(sizeof(t_pwd));
    getcwd(buffer, sizeof(buffer));
    (*wds) = (t_pwd){NULL, ft_strdup(buffer)};   
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
		if (!ptr)
			continue ;
		ptr = ft_expand(ptr, env);
		pos = 0;
		cmd = parsepipe(ptr, &pos, env);
		printf("TYPE CREATED TREE %i\n", cmd->type);
		printf("==================== \n");
		printf("====_PRINT_TREE_==== \n");
    	printf("==================== \n");
    // print_tree(cmd);
		ft_execution(cmd, env, wds);
		wait(0);
		free(str);
		ft_free_tree(cmd);
	}
	return (0);
}

/**
		for (i = 0; ptr[i]; i++)
			printf("--> %s\n", ptr[i]);
		pos = 0;
		cmd = parsepipe(ptr, &pos, env);
		printf("TYPE CREATED TREE %i\n", cmd->type);
		printf("==================== \n");
		printf("====_PRINT_TREE_==== \n");
		printf("==================== \n");
		print_tree(cmd);
*/
int	main(int ac, char **av, char **envp)
{
	t_env_v	*env;

	(void)ac;
	(void)av;
	env = env_init(envp);
	if (!env)
		exit(-1);
	ft_run_shell(env);
	// system("leaks min÷ishell");
}
