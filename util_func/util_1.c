/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 23:43:26 by serraoui          #+#    #+#             */
/*   Updated: 2024/03/31 23:24:32 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

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

t_env_v *ft_lstlast(t_env_v *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void ft_lstadd_back(t_env_v **lst, t_env_v *new)
{
	t_env_v *tmp;

	if (!lst)
		return;
	if (!(*lst))
	{
		(*lst) = new;
		return;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
}

void ft_list_remove_if(t_env_v **begin_list, void *data_ref, int (*cmp)(char *, char *))
{
	if (begin_list == NULL || *begin_list == NULL)
		return;

	t_env_v *node = (*begin_list);

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

char **ft_split_2(char *s, char c)
{
	char **ptr;
	int i;
	char *str;

	//!toremove
	(void)c;
	ptr = malloc(sizeof(char *) * 2);
	if (!ptr)
		return (NULL);
	// todo! change strdup by ft_strdup
	str = ft_strdup(s);
	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	ptr[0] = str;
	str[i++] = 0;
	ptr[1] = (str + i);
	return (ptr);
}

/*
	@OTHOR: hicham bouzid
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