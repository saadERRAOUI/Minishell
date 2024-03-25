/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:02:20 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/25 03:00:50 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_env_v
{
	char    		*key;
	char			*value;
	struct	s_env_v	*next;
}				t_env_v;

int     ft_strcmp(char *s1, char *s2);
int     ft_putstr_fd(char *s, int fd);
int     ft_strlen(char *str);
int		count_words(char const *s, char c);
char    *ft_strchr(const char *s, int c);
char    **ft_split(char const *s, char c);
void	ft_lstadd_back(t_env_v **lst, t_env_v *new);
void    ft_env(t_env_v *env);
void	ft_export(t_env_v **env, char *s);

#endif