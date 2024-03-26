/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 23:43:26 by serraoui          #+#    #+#             */
/*   Updated: 2024/03/26 06:59:42 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int      count_words(char const *s, char c)
{
        int     i;
        int     chuncks_number;

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

int	is_separator(char s, char c)
{
	return ((c == s));
}

int	ft_count(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!is_separator(s[0], c))
	{
		count++;
		i++;
	}
	while (s[i])
	{
		if (is_separator(s[i], c) && s[i + 1] && !is_separator(s[i + 1], c))
			count++;
		i++;
	}
	return (count);
}

char	**ft_free(int index, char **ptr)
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

char	**ft_alloc(char **ptr, const char *s, char c, int e)
{
	int	i;
	int	j;
	int	f;

	i = 0;
	j = 0;
	while (s[i] && j != e)
	{
		while (is_separator(s[i], c) && s[i])
			i++;
		f = i;
		if (!s[f])
			break ;
		while (!is_separator(s[f], c) && s[f])
			f++;
		ptr[j] = malloc(sizeof(char) * (1 + f - i));
		if (!ptr[j])
			return (ft_free(j - 1, ptr));
		f = 0;
		while (s[i] && !is_separator(s[i], c))
			ptr[j][f++] = s[i++];
		ptr[j][f] = 0;
		j++;
	}
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		count;

	if (!s || !*s)
	{
		ptr = malloc(sizeof(char *));
		if (!ptr)
			return (NULL);
		ptr[0] = 0;
		return (ptr);
	}
	count = ft_count(s, c);
	ptr = malloc(sizeof(char *) * (count + 1));
	if (!ptr)
		return (NULL);
	ptr[count] = 0;
	return (ft_alloc(ptr, s, c, count));
}

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

void ft_list_remove_if(t_env_v **begin_list, void *data_ref, int (*cmp)(char *, char *))
{
    if (begin_list == NULL || *begin_list == NULL)
        return;
        
    t_env_v *node = (*begin_list);
    
    if (!cmp((char *)node->key, (char *)data_ref))
    {
        (*begin_list) = (*begin_list)->next;
        free(node);
        ft_list_remove_if(begin_list, data_ref, cmp);
    }
    else
    {
        node = (*begin_list);
        ft_list_remove_if(&(node->next), data_ref, cmp);
    }
}