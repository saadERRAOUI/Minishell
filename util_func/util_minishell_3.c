/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_minishell_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:23:09 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/03 18:23:04 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
	@AUTHOR: hicham bouzid
	@PROTOTYPE: int ft_strlen_until(char *str, char c)
	@DESC: function like strchr but this return the index
	@DATE: 16-04-2024
*/

int	ft_strlen_until(char *str, char c)
{
	int	i;

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

/*
	@AUTHOR: Hicham bouzid
	@PROTOTYPE: char	*ft_modifie(char *ptr, int start, int end, char *t)
	@DESC: realloc for a new strin by adding the value of a env variable
			if it's found else remove it's.
	@DATE: 18-04-2024
*/

char	*ft_modifie(char *ptr, int start, int end, char *t)
{
	int		len;
	char	*str;
	int		i;
	int		j;

	len = ft_strlen(ptr) - (end - start) - 1;
	if (t)
		len += ft_strlen(t);
	str = malloc(sizeof(char) * (len));
	str[len] = 0;
	i = 0;
	j = 0;
	while (i < len)
	{
		while (i < start - 1)
		{
			str[i] = ptr[i];
			i++;
		}
		while (t && t[j])
			str[i++] = t[j++];
		while (i < len && end < (int)ft_strlen(ptr))
			str[i++] = ptr[end++];
	}
	return (str);
}

/*
	@AUTHOR: Hicham BOUZID
	@PROTOTYPE: char	*get_measurements(int *index, int *len, char *ptr)
	@DESC: function uset to get index of start and end of env variable
	@DATE: 18-04-2024
*/

char	*get_measurements(int *index, int *len, char *ptr)
{
	*index = ft_strlen_until(ptr, '$');
	*len = *index;
	while (ptr[*len])
	{
		if (ptr[*len] == '\"' || ptr[*len] == ' ' || ptr[*len] == '\'')
			break ;
		(*len)++;
	}
	return (ft_substr(ptr, *index, *len - *index));
}

/*
	@AUTOR: hicham bouzid
	@PRORTOTYPE: char	*ft_replace_dollar(char *ptr, t_env_v *env)
	@DESC: just check if the env variable found and replace it else
	remove the word containe $ from the string
	@DATE: 18-05-2024
*/

char	*ft_replace_dollar(char *ptr, t_env_v **env)
{
	char	*s1;
	char	*s2;
	int		index;
	int		len;

	s2 = NULL;
	s1 = 0;
	if (ft_strlen_until(ptr, '$') != -1)
	{
		s1 = get_measurements(&index, &len, ptr);
		s1 = ft_substr(ptr, index, len - index);
		while ((*env))
		{
			if (!ft_strcmp((*env)->key, s1))
			{
				s2 = (*env)->value;
				break ;
			}
			(*env) = (*env)->next;
		}
		free(s1);
		s1 = ft_modifie(ptr, index, len, s2);
	}
	return (s1);
}

char	**ft_split_2(char *s, char c)
{
	char	**ptr;
	int		i;
	char	*str;

	(void)c;
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
