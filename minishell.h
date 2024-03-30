/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:02:20 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/27 01:14:12 by hibouzid         ###   ########.fr       */
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

#include "./libft/libft.h"

typedef struct s_env_v
{
	char *key;
	char *value;
	struct s_env_v *next;
} t_env_v;
int ft_strcmp(char *s1, char *s2);
char **ft_split_2(char *s, char c);
void ft_export(t_env_v **env, char *s);
void ft_env(t_env_v *env);
int count_words(char const *s, char c);
void ft_list_remove_if(t_env_v **begin_list,
					   void *data_ref, int (*cmp)(char *, char *));
t_env_v *ft_lstlast(t_env_v *lst);
void ft_lstadd_back(t_env_v **lst, t_env_v *new);
void ft_unset(t_env_v **env, char *key);
// int     ft_putstr_fd(char *s, int fd);
// int     ft_strlen(char *str);
// char    *ft_strchr(const char *s, int c);

#endif