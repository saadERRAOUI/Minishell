/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:35:11 by hibouzid          #+#    #+#             */
/*   Updated: 2024/05/12 23:29:16 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	if (len == 0 || !s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (NULL);
	j = start;
	while (s[j++] && len > i)
		i++;
	str = malloc(sizeof(char) * (1 + i));
	if (!str)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
		str[i++] = s[start++];
	str[i] = 0;
	return (str);
}
