/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_minishell_6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:21:26 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/09 15:12:41 by hibouzid         ###   ########.fr       */
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
