/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:02:20 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/11 16:04:43 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <termios.h>
# include <unistd.h>

# define MAXARGS 100
# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LEFT 4
# define RIGHT 5
# define SPACE2 6
# define DL 7
# define EXIT_FAILUR 127
# define CTRL_C 130

//error files Command errors Signal  Syntax error
//extern
int s_exit;

typedef struct s_redircmd t_redircmd;
typedef struct s_pwd
{
	char *old_wd;
    char *curr_wd;
}   t_pwd;

typedef struct s_env_v
{
	char					*key;
	char					*value;
	struct s_env_v			*next;
}							t_env_v;

typedef struct s_cmd
{
	int						type;
}							t_cmd;

typedef struct s_pipecmd
{
	int						type;
	t_cmd					*left;
	t_cmd					*right;
}							t_pipecmd;

typedef struct s_execcmd
{
	int						type;
	char					**argv;
	char					*path;
	char					**envp;
}							t_execcmd;

typedef struct s_redircmd
{
	int						type;
	t_cmd					*cmd;
	char					*file;
	int						mode;
	int token;
	int						fd;
	t_redircmd				*next;
}							t_redircmd;

int					ft_strcmp(char *s1, char *s2);
int					count_words(char const *s, char c);
int					peek(char **ps, char *es, char *toks);
// void				ft_export(t_env_v **env, char *s);
void				ft_export(t_env_v **env, char **av);
void				ft_env(t_env_v *env);
void				ft_list_remove_if(t_env_v **begin_list, void *data_ref,
                        int (*cmp)(char *, char *));
void				ft_lstadd_back(t_env_v **lst, t_env_v *new);
void                ft_lstadd_back_(t_redircmd **lst, t_redircmd *new);
void				ft_unset(t_env_v **env, char *key);
void				ft_free_stack(t_env_v **a);
t_env_v				*ft_lstlast(t_env_v *lst);
t_env_v				*env_init(char **env);
t_cmd				*parsepipe(char **ps, int *pos, t_env_v *env);
t_cmd				*parsexec(char **ps, int *pos, t_env_v *env);
t_cmd				*execcmd(void);
t_cmd				*pipecmd(t_cmd *left, t_cmd *right);
t_redircmd          *ft_lstlast_(t_redircmd *lst);
t_redircmd          *redircmd(char *file, int mode, int fd);
char				*ft_charjoin(char *str, char c);
char				*add_32(char *str, char *sym);
char				*ft_convert_0(char *str);
char				**undo(char **ptr);
char				**ft_split_2(char *s, char c);
char				**ft_check_syntax(char *str);
char				*ft_replace_dollar(char *ptr, t_env_v *env);
char				**add_dollar(char **ptr, t_env_v *env);
char				*expand_or_not(char *ptr);
char				*ft_shift(char *ptr);
char                **ft_parce_env(char **env);
char                **get_envp(t_env_v *env);
char                *ft_cmd_valid(char **env, char **cmd);
char                **ft_free(int index, char **ptr);
char                **syntax(char **ptr);
int					ft_lst_size(t_env_v *lst);
int					get_token_type(char *s);
int					ft_handel_line(char *str);
int					ft_util_quotes(char *av, char q, int *index);
int					ft_quotes(char *str);
int					ft_strlen_until(char *str, char c);
int					ft_back(char *str, int index);
int                 pwd(t_pwd *wds);
int                 echo(int ac, char **av);
int                 ft_strleen(char **ptr);
void                signal_handler(int sig);
void                parseredir(t_redircmd **red, char **ps, int *pos, t_env_v *env);
void                ft_free_tree(t_cmd *cmd);
void                ft_exit(int ac, char **av);
void                cd(char **av, t_pwd *wds);
void                ft_here_doc(t_redircmd **cmd, t_env_v *env, char *delimeter);
void                ft_print_tab(char **s);
void                ft_free_tree(t_cmd *cmd);
void                child_exit(int status);
void                child_signal_def(int flag);
char				*get_name(void);
void				ft_free2(char **ptr);

#endif
