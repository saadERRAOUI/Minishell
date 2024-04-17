/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:02:17 by serraoui          #+#    #+#             */
/*   Updated: 2024/04/17 11:54:21 by hibouzid         ###   ########.fr       */
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
}
