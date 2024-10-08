/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 23:43:26 by serraoui          #+#    #+#             */
/*   Updated: 2024/05/13 01:24:11 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

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

t_redircmd	*ft_lstlast_(t_redircmd *lst)
{
	if (!lst)
		return (lst);
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_(t_redircmd **lst, t_redircmd *new)
{
	t_redircmd	*save;

	if (!lst)
		return ;
	save = *lst;
	if (!*lst && new)
	{
		*lst = new;
		return ;
	}
	save = ft_lstlast_(save);
	save->next = new;
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
		free(node->value);
		free(node);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
	{
		node = (*begin_list);
		ft_list_remove_if(&(node->next), data_ref, cmp);
	}
}

int	ft_handel_line(char *str, t_env_v *env)
{
	if (!str)
	{
		ft_free_stack(&env);
		exit(0);
	}
	if (!*str || !only_char(str, ' ') || !only_char(str, '\t')
		|| !ft_strcmp(str, "\n") || !ft_quotes(str))
	{
		free(str);
		return (0);
	}
	else
		add_history(str);
	return (1);
}
