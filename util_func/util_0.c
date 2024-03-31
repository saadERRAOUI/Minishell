/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:01:05 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/30 02:28:22 by hibouzid         ###   ########.fr       */
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

int count_words(char const *s, char c)
{
	int i;
	int chuncks_number;

	i = 0;
	chuncks_number = 0;
	if (*s == '\0')
		return (chuncks_number);
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			chuncks_number += 1;
		i++;
	}
	if (s[i - 1] != c)
		chuncks_number += 1;
	return (chuncks_number);
}

char **ft_free(int index, char **ptr)
{
	if (index == 0)
	{
		free(ptr);
		return (0);
	}
	while (index >= 0)
	{
		if (ptr[index])
			free(ptr[index]);
		index--;
	}
	free(ptr);
	return (0);
}

char **ft_split_2(char *s, char c)
{
	char **ptr;
	int i;
	char *str;

	ptr = malloc(sizeof(char *) * 2);
	if (!ptr)
		return (NULL);
	str = ft_strdup(s);
	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	ptr[0] = str;
	str[i++] = 0;
	ptr[1] = (str + i);
	return (ptr);
}