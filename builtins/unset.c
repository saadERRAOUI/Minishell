/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:46:17 by serraoui          #+#    #+#             */
/*   Updated: 2024/05/03 21:56:13 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	ft_unset(t_env_v **env, char *key)
{
	if (!key || !env)
		return ;
	ft_list_remove_if(env, key, ft_strcmp);
	ft_env(*env);
}
