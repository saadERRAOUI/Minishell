/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_minishell_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:23:09 by hibouzid          #+#    #+#             */
/*   Updated: 2024/04/17 11:35:19 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
	@AUTHER: hicham bouzid
	@PROTOTYPE: int ft_strlen_until(char *str, char c)
	@DESC: function like strchr but this return the index
	@DATE: 16-04-2024
*/

int ft_strlen_until(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (str[i + 1])
				return (i + 1);
			else
				return (-1);
		}
		i++;	
	}
	return (-1);
}

char *ft_replace_dollar(char *ptr, t_env_v *env)
{
	char *s1;
	char *s2;
	int index;
	int len;
	int i;
	int j;

	s2 = NULL;
	i = 0;
	j = 0;
	if (ft_strlen_until(ptr, '$') != -1)
	{
		index = ft_strlen_until(ptr, '$');
		len = index;
		while (ptr[len])
		{
			if (ptr[len] == '\"' || ptr[len] == ' ')
			break ;
			len++;
		}
		s1 = ft_substr(ptr, index, len - index);
		while (env)
		{
			if (!ft_strcmp(env->key, s1))
			{
				s2 = env->value;
				break ;
			}
			env = env->next;
		}
		// free(s1);
		i = ft_strlen(ptr) - (len - index);
		// printf("->:%d\n", (int)ft_strlen(ptr));
		if (s2)
			i += ft_strlen(s2);
		s1 = malloc(sizeof(char) * (i));
		s1[i] = 0;
		while (j < i)
		{
			while (j < index)
			{
				s1[j] = ptr[j];
				j++;
			}
					
		}
		// printf("--> %d\n", (int)ft_strlen(s2));
	}
	return (s2);
}