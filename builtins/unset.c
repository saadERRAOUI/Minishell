/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:46:17 by serraoui          #+#    #+#             */
/*   Updated: 2024/04/17 11:58:05 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	ft_unset(t_env_v **env, char *key)
{
	if (!key || !env)
		return ;
	ft_list_remove_if(env, key, ft_strcmp);
}
