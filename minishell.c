/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:15:26 by serraoui          #+#    #+#             */
/*   Updated: 2024/05/09 15:18:59 by hibouzid         ###   ########.fr       */
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

/*
static void print_tree(t_cmd *tree)
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

void	ft_pipe(t_pipecmd *cmd, t_env_v *env)
{
	pid_t	pid;
	pid_t	pid1;
	int		pip[2];
    int     s;

	// int in = dup(0);
	// int out = dup(1);
    // signal(SIGQUIT, SIG_IGN);
    // signal(SIGINT, SIG_IGN);
    child_signal_def(2);
	if (pipe(pip) == -1)
	{
		ft_putstr_fd("problem in pipe\n", 2);
		exit(-1); //check exit status
	}
	pid = fork();
	if (pid < 0)
		ft_putstr_fd("error in fork child 1\n", 2);
	if (pid == 0)
	{
        // signal(SIGQUIT, SIG_DFL);
        // signal(SIGINT, SIG_DFL);
        child_signal_def(1);
		close(pip[0]);
		dup2(pip[1], 1);
		close(pip[1]);
		ft_execution(cmd->left, env, NULL);
		exit(0);
	}
	pid1 = fork();
	if (pid1 < 0)
		ft_putstr_fd("error in fork child 2\n", 2);
	if (pid1 == 0)
	{
        // signal(SIGQUIT, SIG_DFL);
        // signal(SIGINT, SIG_DFL);
        child_signal_def(1);
		close(pip[1]);
		dup2(pip[0], 0);
		close(pip[0]);
		ft_execution(cmd->right, env, NULL);
		exit(0);
	}
	close(pip[0]);
	close(pip[1]);
	// waitpid(pid, NULL, 0);
	// waitpid(pid1, NULL, 0);
	wait(&s);
    child_exit(s);
	// wait(0);
}

int ft_builtin_orch(char **argv, t_execcmd *cmd, t_env_v **env, t_pwd *wds)
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
    int         s;
	(void)env;

	cd = (t_execcmd *)cmd;
    // signal(SIGQUIT, SIG_IGN);
    // signal(SIGINT, SIG_IGN);
    child_signal_def(2);
	if (ft_builtin_orch(cd->argv, cd, &env, wds))
		return ;
	if (!cd->path)
	{
		ft_putstr_fd("command not found\n", 2);
		return ;
	}
	else
	{
		if (fork() == 0) {
            // signal(SIGQUIT, SIG_DFL);
            // signal(SIGINT, SIG_DFL);
            child_signal_def(1);
            if (execve(cd->path, cd->argv, cd->envp) == -1)
                ft_putstr_fd("error happen in execve\n", 2);
            //exit(-1); //!todo : add errno
        }
        else {
		    wait(&s);
            child_exit(s);
        }
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

//! todo  remove expand from delimeter here_doc
void ft_here_doc(t_redircmd **cmd, t_env_v *env, char *delimeter)
{
	// char	*tmp;
	char	*str;
	char	*tm;
    // int     flag;

	// tmp = get_name();
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
	// free((*cmd)->file);
	// (*cmd)->file = tmp;
}

void	redir_cmd(t_cmd *cmd, t_env_v *env)
{
	t_redircmd	*redir;
	int			in;
	int			out;

	redir = (t_redircmd *)cmd;
	in = dup(0);
	out = dup(1);
	int in_ = dup(0);
	int out_ = dup(1);
	while (redir)
	{
		if (redir->fd == 0)
		{
			redir->fd = open(redir->file, O_RDONLY);
            printf("[CMD-HERE] %i\n", cmd->type);
            printf("[CMD-HERE] %s\n", ((t_redircmd *)cmd)->file);
            printf("[CMD-HERE] %p\n", ((t_redircmd *)cmd)->cmd);
            printf("[CMD-HERE] %d\n", ((t_redircmd *)cmd)->mode);
			if (redir->fd < 0)
				ft_putstr_fd("no such file of directory\n", 2);
			if (dup2(redir->fd, in) == -1)
				printf("dup2\n");

		}
		else if (redir->fd == 1 && redir->mode)
		{
			redir->fd = open(redir->file, O_CREAT | O_RDWR | O_APPEND, 0664);
				if (redir->fd < 0)
					ft_putstr_fd("problem in open function\n", 2);
				if (dup2(redir->fd, out) == -1)
				printf("dup3\n");
		}
		else if (redir->fd == 1)
		{
			redir->fd = open(redir->file, O_CREAT | O_RDWR | O_TRUNC, 0664);
			if (redir->fd < 0)
				ft_putstr_fd("problem in open function\n", 2);
			if (dup2(redir->fd, out) == -1)
			printf("dup4\n");
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
    int     s;
	if (cmd->type == 3)
        ft_pipe((t_pipecmd *)cmd, env);
	else if (cmd->type == 2)
		redir_cmd(cmd, env);
	else if (cmd->type == 1)
		ft_execut(cmd, env, wds);
    wait(&s);
    child_exit(s);
}

void    disable_raw_mode(void)
{
    struct termios    new_termios;
    struct termios    orig_termios;

    tcgetattr(0, &orig_termios);
    new_termios = orig_termios;
    new_termios.c_lflag &= ~ECHOCTL;
    tcsetattr(0, TCSANOW, &new_termios);
}

static void ft_here(void)
{
	// return ;
	system("leaks minishell");
}

int	ft_run_shell(t_env_v *env)
{
	t_cmd	*cmd;
	char	*str;
    // char    buffer[1024];
	char	**ptr;
	int		pos;
    // t_pwd   *wds;

    // wds = malloc(sizeof(t_pwd));
    // getcwd(buffer, sizeof(buffer));
    // (*wds) = (t_pwd){NULL, ft_strdup(buffer)};
	// (void)cmd;
    // signal(SIGQUIT, handler);
    // signal(SIGINT, handler);
    child_signal_def(0);
	while (1)
	{
		str = readline("$ ");
		// printf("ft_strleen %d:\n", (int)ft_strlen(str));
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
        ft_execution(cmd, env, NULL);
		ft_free_tree(cmd);
		printf("sizeof :%lu\n", sizeof());
		free(str);
		ft_here();
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
	// if (!env)
	// 	exit(-1);
    // disable_raw_mode();
	ft_run_shell(env);
}
