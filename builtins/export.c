/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:40:47 by serraoui          #+#    #+#             */
/*   Updated: 2024/03/25 02:58:52 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	ft_export(t_env_v **env, char *s) //! Can be returning boolean //
{
	char	**_s;
	t_env_v	*node;

	if (!s)
		return ;
	_s = ft_split(s, '=');
	if (!_s)
		return ;
	node = (t_env_v *)malloc(sizeof(t_env_v));
	if (!node)
		return ;
	if (count_words(s, '=') >= 2)
	{
		(*node) = (t_env_v){_s[0], _s[1], NULL};
		ft_lstadd_back(env, node);
	}
}