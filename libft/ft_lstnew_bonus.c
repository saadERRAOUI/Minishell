/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:04:17 by hibouzid          #+#    #+#             */
/*   Updated: 2023/11/13 12:11:33 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

// #include<stdio.h>

// int main()
// {
// 	int nb  = 42;
// 	t_list *ptr;

// 	ptr = ft_lstnew((void *)&nb);
// 	printf("--> %d\n", *((int *)ptr->content));
// }
