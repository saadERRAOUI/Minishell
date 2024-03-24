/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:02:20 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/24 03:25:31 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int     ft_strcmp(char *s1, char *s2);
int     ft_putstr_fd(char *s, int fd);
int     ft_strlen(char *str);
char    *ft_strchr(const char *s, int c);

#endif