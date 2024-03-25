/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:22:15 by hibouzid          #+#    #+#             */
/*   Updated: 2023/11/16 11:16:39 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*save;

	save = *lst;
	if (!*lst && !new)
		return ;
	if (!*lst && new)
	{
		*lst = new;
		return ;
	}
	save = ft_lstlast(save);
	save->next = new;
}
