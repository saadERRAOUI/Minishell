/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_minishell_6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:21:26 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/12 22:36:51 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	@AUTHOR: hicham bouzid
	@PROTO: void ft_free_stack():
	@DESC: free the the env alloceted if the programme ended or
			failed
	@DATE: 29-03-2024
*/
void	ft_free_stack(t_env_v **a)
{
	t_env_v	*tmp;

	if (!a || !*a)
		return ;
	tmp = *a;
	while ((*a))
	{
		tmp = *a;
		*a = (*a)->next;
		free(tmp->key);
		free(tmp);
	}
}

/*
	@AUTHOR: Hicham BOUZID
	@PROTOTYPE: int	ft_strleen(char **ptr)
	@DESC: count lenght of an array tow dimention
	@DATE: 21-04-2024
*/

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

/*
	@AUTHOR: hicham bouzid
	@DESC: join a char to an string
	@PROTOTYPE: char *ft_charjoin(char *str,
		char c)
	@DATE: 03-04-2024
*/

char	*ft_charjoin(char *str, char c)
{
	int		len;
	char	*ptr;

	if (!str)
	{
		ptr = malloc(sizeof(char) * (2));
		ptr[0] = c;
		ptr[1] = 0;
		return (ptr);
	}
	len = (int)ft_strlen(str);
	ptr = malloc(sizeof(char) * (len + 2));
	if (!ptr)
		return (NULL);
	ptr[len + 1] = 0;
	len = 0;
	while (str[len])
	{
		ptr[len] = str[len];
		len++;
	}
	ptr[len] = c;
	free(str);
	return (ptr);
}

void	ft_free2(char **ptr)
{
	while ((*ptr))
	{
		free(*ptr);
		*ptr = NULL;
		ptr++;
	}
	free(ptr);
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
