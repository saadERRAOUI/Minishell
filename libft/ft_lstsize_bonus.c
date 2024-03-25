/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:47:54 by hibouzid          #+#    #+#             */
/*   Updated: 2023/11/16 11:12:35 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*ptr;

	if (!lst)
		return (0);
	i = 0;
	ptr = lst;
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	ptr1;
// 	t_list	ptr2;
// 	t_list	ptr3;
// 	char	tab1[] = "15672";
// 	char	tab2[] = "15672";
// 	char	tab3[] = "15672";

// 	ptr1.content = tab1;
// 	ptr1.next = &ptr2;
// 	ptr2.content = tab2;
// 	ptr2.next = &ptr3;
// 	ptr3.content = tab3;
// 	ptr3.next = NULL;

// 	printf("%d\n", ft_lstsize(&ptr1));
// }
