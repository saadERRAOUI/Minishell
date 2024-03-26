/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:40:47 by serraoui          #+#    #+#             */
/*   Updated: 2024/03/26 08:10:23 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void ft_export(t_env_v **env, char *s) //! Can be returning boolean //
{
	char **_s;
	t_env_v *node;

	if (!s)
		return;
	_s = ft_split_2(s, '=');
	if (!_s)
		return;
	node = malloc(sizeof(t_env_v));
	if (!node)
		return;
	if (count_words(s, '=') >= 2)
	{
		(*node) = (t_env_v){_s[0], _s[1], NULL};
		ft_lstadd_back(env, node);
	}
	free(_s);
}