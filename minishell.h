/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:02:20 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/28 16:05:11 by hibouzid         ###   ########.fr       */
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
#include <readline/history.h>
#include <readline/readline.h>
#include "./libft/libft.h"

int ft_strcmp(char *s1, char *s2);
// int     ft_putstr_fd(char *s, int fd);
// int     ft_strlen(char *str);
// char    *ft_strchr(const char *s, int c);

typedef struct s_env_v
{
	char *key;
	char *value;
	struct s_env_v *next;
} t_env_v;

#endif