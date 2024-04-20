/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 23:43:26 by serraoui          #+#    #+#             */
/*   Updated: 2024/04/19 17:32:40 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

t_env_v	*ft_lstlast(t_env_v *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_env_v **lst, t_env_v *new)
{
	t_env_v	*tmp;

	if (!lst)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
}

void	ft_list_remove_if(t_env_v **begin_list, void *data_ref,
		int (*cmp)(char *, char *))
{
	t_env_v	*node;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	node = (*begin_list);
	if (!cmp((char *)node->key, (char *)data_ref))
	{
		(*begin_list) = (*begin_list)->next;
		free(node->key);
		free(node);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
	{
		node = (*begin_list);
		ft_list_remove_if(&(node->next), data_ref, cmp);
	}
}

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

int	ft_handel_line(char *str)
{
	if (!*str || !ft_strcmp(str, "\n") || !ft_quotes(str))
	{
		free(str);
		return (0);
	}
	else
		add_history(str);
	return (1);
}
