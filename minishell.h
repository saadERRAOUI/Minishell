/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:02:20 by hibouzid          #+#    #+#             */
/*   Updated: 2024/04/09 15:38:58 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "./libft/libft.h"

#define MAXARGS 100
#define EXEC 1
#define REDIR 2
#define PIPE 3
#define LEFT 4
#define RIGHT 5
#define SPACE 6

#define EXIT_FAILUR 127
#define CTRL_C 130
typedef struct s_env_v
{
	char *key;
	char *value;
	struct s_env_v *next;
} t_env_v;

typedef struct s_cmd
{
	int type;
} t_cmd;

typedef struct s_pipecmd
{
	int type;
	t_cmd *left;
	t_cmd *right;
} t_pipecmd;

typedef struct s_execcmd
{
	int type;
	char **argv; //TODO : update this pointer to be allocated
} t_execcmd;

typedef struct s_redircmd
{
	int type;
	t_cmd *cmd;
	char *file;
	int mode;
	int fd;
} t_redircmd;

int ft_strcmp(char *s1, char *s2);
int count_words(char const *s, char c);
int getToken(char **ps, char *es, char **q, char **eq);
int peek(char **ps, char *es, char *toks);
char **ft_split_2(char *s, char c);
void ft_export(t_env_v **env, char *s);
void ft_env(t_env_v *env);
void ft_list_remove_if(t_env_v **begin_list,
					   void *data_ref, int (*cmp)(char *, char *));
void ft_lstadd_back(t_env_v **lst, t_env_v *new);
void ft_unset(t_env_v **env, char *key);
void ft_free_stack(t_env_v **a);
t_env_v *ft_lstlast(t_env_v *lst);
t_env_v *env_init(char **env);
t_cmd  *parseredir(t_cmd *cmd, char **ps, int *pos);
t_cmd  *parsepipe(char **ps, int *pos);
t_cmd  *parsexec(char **ps, int *pos);
t_cmd *execcmd(void);
t_cmd *redircmd(t_cmd *subcmd, char *file, int mode, int fd);
t_cmd *pipecmd(t_cmd *left, t_cmd *right);
int	get_token_type(char *s);

int ft_handel_line(char *str);
char *ft_charjoin(char *str, char c);
char *add_32(char *str, char *sym);
int ft_quotes(char *str);
int ft_util_quotes(char *av, char q, int *index);
char *ft_convert_0(char *str);
char **undo(char **ptr);
char **ft_check_syntax(char *str);

void ft_print_tab(char **s);

#endif