/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:01:05 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/26 06:59:58 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}

int ft_putstr_fd(char *s, int fd)
{
	return (write(fd, s, ft_strlen(s)));
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char    *ft_strchr(const char *s, int c)
{
        char    character;

        character = (char) c;
        if (character == '\0' && s)
                return ((char *)(s + ft_strlen((char *)s)));
        while (*s)
        {
                if (*s == (char)character)
                        return ((char *)s);
                s++;
        }
        if (character == '\0')
                return ((char *)s);
        return (NULL);
}

int	ft_strleen(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (0);
	while (ptr[i])
		i++;
	return (i);
}
