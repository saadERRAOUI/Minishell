/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:15:26 by serraoui          #+#    #+#             */
/*   Updated: 2024/05/03 21:53:31 by serraoui         ###   ########.fr       */
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
void ft_execut(t_cmd *cmd, t_env_v *env);
void ft_execution(t_cmd *cmd, t_env_v *env);

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
		if (((t_execcmd *)tree)->path)
			printf("path: %s\n", ((t_execcmd *)tree)->path);
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

// void procces(t_execcmd *cmd, int fd, int pip, int mode)
// {
// 	char *path;
// 	if (mode == 0)
// 	{
// 		if (dup2(fd, 0) == -1 || dup2(pip, 1) == -1)
// 			ft_putstr_fd("error in dup function\n", 2);
// 		close(fd);
// 		close(pip);
// 		if (execve(cmd->argv, cmd->path, cmd->envp) == -1)
// 			ft_putchar_fd("error in execve 1\n", 2);

// 	}
// 	else if (mode == 1)
// 	{
// 		if (dup2(pip, 0) == -1|| dup2(fd, 1) == -1)
// 			ft_putstr_fd("error in dup function\n", 2);
// 		close(0);
// 		close(1);
// 		if (execve(cmd->argv, cmd->path, cmd->envp) == -1)
// 			ft_putchar_fd("error in execve 2\n", 2);
// 	}
// }

// char *get_path(v)
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

void ft_procces(t_cmd *cmd, int mode, int *pip, t_env_v *env)
{
	t_pipecmd *cd;
	// t_execcmd *c;

	cd = (t_pipecmd *)cmd;
	if (mode == 0)
	{
		close(pip[0]);
		dup2(pip[1], 1);
		close(pip[1]);
			ft_execution(cd->left, env);
	}
	else if (mode == 1)
	{
		close(pip[0]);
		dup2(pip[1], 1);
		close(pip[1]);
		ft_execution(cd->right, env);
	}
	close(0);
	close(1);
	return ;
}

void ft_pipe(t_pipecmd *cmd ,t_env_v *env)
{
	pid_t pid;
	pid_t pid1;
	int pip[2];


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
		// ft_procces(cmd, 0, pip, env);
		ft_execution(cmd->left, env);
	}
	pid1 = fork();
	if (pid1 < 0)
		ft_putstr_fd("error in fork child 2\n", 2);
	if (pid1 == 0)
	{

		close(pip[1]);
		dup2(pip[0], 0);
		close(pip[0]);
		ft_execution(cmd->right, env);
		// ft_procces(cmd, 1, pip, env);
	}
	close(pip[0]);
	close(pip[1]);
	wait(0);
	wait(0);
}

int ft_builtin_orch(char **argv, t_execcmd *cmd, t_env_v **env)
{
	if (!argv || !argv[0])
        return (0);
	
    if (!ft_strcmp("echo", argv[0])) //echo
        return (echo(ft_strleen(cmd->argv), cmd->argv), 1);
    // else if (!ft_strcmp("cd", argv[0]))
    //     exit(-1); //!toRemove //Todo :  call cd function;
    else if (!ft_strcmp("pwd", argv[0]))
        return (pwd(ft_strleen(cmd->argv), cmd->argv), 1);
    else if (!ft_strcmp("export", argv[0]))
        return (ft_export(env, cmd->argv[1]), 1);
    else if (!ft_strcmp("unset", argv[0]))
        return (ft_unset(env, cmd->argv[1]), 1);
    else if (!ft_strcmp("env", argv[0]))
        return (ft_env((*env)), 1);
    // else if (!ft_strcmp("exit", argv[0]))
    //     ft_exit(); //*call kill to send exit signal
	return (0);
}

void ft_execut(t_cmd *cmd, t_env_v *env)
{
	t_execcmd *cd;
	(void)env;

	cd = (t_execcmd *)cmd;
	if (ft_builtin_orch(cd->argv, cd, &env))        
		// //Todo : add custom logic for built-ins
		// ft_builtin_orch(cd->argv, cd, &env);
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

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while ((s1[i] || s2[i]) && (i < n))
// 	{
// 		if ((unsigned char)s1[i] != (unsigned char)s2[i])
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 		i++;
// 	}
// 	return (0);
// }
/**

void ft_here_doc(t_cmd *cmd, t_env_v *env)
{
	int fd[2];
	char *str;
	// int in;
	char *tmp;
	// int out;

	t_redircmd *cd;

	cd = (t_redircmd *)cmd;

	// int out = dup(1);
	// // in = dup(0);
	// if (fork() == 0)
	// {
	// 	// close(1);
	// ¬if (fork() == 0)
	// {
		if (pipe(fd) == -1)
		{
			ft_putstr_fd("problem in pipe here_doc\n", 2);
			exit (-1);
		}
		// close(fd[0]);
		if (dup2(fd[1], 1) == -1)
		{
			ft_putstr_fd("problem in dup2\n", 2);
			exit(-1);
		}
		close(fd[1]);
		// close(ou);
		// printf("here\n");
		while(1)
		{
			str = readline("heredoc> ");
			// printf("---->> %d\n", (int)ft_strlen(str));
			if (!ft_strcmp(str, cd->file))
			{
			printf("11111111111\n");
				free(str);
				dup2(fd[0], 0);
				// dup2(out, 1);
				// close(out);
				// close(fd[1]);
				exit(0);
				// exit(0);
			}
			if (str && ft_strchr(str, '$'))
				{
					printf("2222\n");
					tmp = str;
					str = ft_replace_dollar(str, env);
					free(tmp);
				}
			// str = *add_dollar(&str, env);
			// printf("12121212\n");
			ft_putstr_fd(str, 1);
			free(str);
		}
		// dup2(fd[0], 0);
		// close();
		// close(fd[1]);
	// }
	// else
	// 	return ;
	// wait(0);
}
*/

/*
	@AUTHOR: BOUZID Hicham
	@DESC: get a random name for a temporary file
		for a here_doc
	@DATE: 02-05-2024
*/

char *get_name(void)
{
	char *name;
	char c;
	char *tmp;
	int fd;
	int i;

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
		// i++;
	}
	close(fd);
	tmp = name;
	name = ft_strjoin(ft_strdup("/tmp/"), name);
	free(tmp);
	return (name);
}

//! todo  remove expand from delimeter here_doc
void ft_here_doc(t_redircmd **cmd, t_env_v *env)
{
	// int f;
	char *tmp;
	char *str;
	char *tm;

	tmp = get_name();
	printf("--->%s\n", tmp);
	// free(tm);
	(*cmd)->fd = open(tmp, O_CREAT | O_RDWR, 0777);
	if ((*cmd)->fd < 0)
		ft_putstr_fd("Error in open function\n", 2);
	while (1)
	{
		str = readline("> ");
		if (!ft_strcmp(str, (*cmd)->file))
			{
				// dup2(redir->fd, 0);
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
	(*cmd)->file = tmp;
	if ((*cmd)->fd < 0)
		ft_putstr_fd("error in  open function \n", 2);
	// dup2((*cmd)->fd, 0);
	// close();
	// return ();
}

void redir_cmd(t_cmd *cmd, t_env_v *env)
{
	t_redircmd *redir;
	int in;
	int out;
	// int token;

	redir = (t_redircmd *)cmd;
	in = dup(0);
	out = dup(1);
	while(redir)
	{
		// token = 0;
		 if (redir->fd == 0 && redir->mode)
		{
			ft_here_doc(&redir, env);
			// token = 1;
			dup2(redir->fd, in);
		}
		else if (redir->fd == 0)
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
		// if (redir->cmd)
		// {
			// if (fork() == 0)
			// wait(0);
		// }
		// if (token == 1)
			// unlink(redir->file);
		// if (cmd)
		if (!redir->next)
			break ;
		close(redir->fd);
		redir = redir->next;
	}
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
	ft_execut(redir->cmd, env);
}

void ft_execution(t_cmd *cmd, t_env_v *env)
{        
	if (cmd->type == 3)
	{
		// (t_pipecmd *)cmd;
		ft_pipe((t_pipecmd *)cmd, env);
	}
	else if (cmd->type == 2)
	{
		redir_cmd(cmd, env);
	}
	else if (cmd->type == 1)
		ft_execut(cmd, env);
	wait(0);     
    // exit(0);
}

// void exec_tree(t_cmd *cmd, t_env_v *env)
// {
// 	if (cmd->type == 3)
// 	{
// 		// if (fork() == 0)
// 		// {
// 		// 	exec_tree(((t_pipecmd *)cmd)->left, env);
// 		// }
// 		// else if (((t_pipecmd *)cmd)->right->type , env) == 2)
// 		// {

// 		// }
// 	}
// 	else if (cmd->type == 2)
// 	{

// 	}
// 	else if (cmd->type == 1)
// 	{
// 		procces();
// 	}
// }
// */

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
		// if (fork() == 0)
		ft_execution(cmd, env);
		wait(0);
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
	// printf("%lu\n", sizeof(t_execcmd));
	// printf("%lu\n", sizeof(t_execcmd *));
	// printf("%lu\n", sizeof(t_cmd));
	// ft_export(&env, ft_strdup("TEEEEEEST=test-"));
	// ft_export(&env, ft_strdup("saad=test"));
	// ft_export(&env, ft_strdup("TEEEEEEST+=saaad+saad+hachmi"));
	// ft_export(&env, ft_strdup("TEEEEEESTE+="));
	// ft_export(&env, NULL);
	// ft_env(env);
	ft_run_shell(env);
}
