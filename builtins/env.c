/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:02:17 by serraoui          #+#    #+#             */
/*   Updated: 2024/05/12 17:22:57 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	ft_env(t_env_v *env)
{
	if (!env)
		return ;
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
    g_exit = 0;
}
