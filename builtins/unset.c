/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:46:17 by serraoui          #+#    #+#             */
/*   Updated: 2024/05/11 20:14:54 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	ft_unset(t_env_v **env, char **key)
{
	if (!key || !env)
		return ;
	key++;
	while (*key)
	{
		ft_list_remove_if(env, *key, ft_strcmp);
		key++;
	}
}
