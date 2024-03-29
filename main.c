/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:11:44 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/28 20:47:45 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char *str;
	while (1)
	{
		str = readline("MINISHELL ");
		add_history(str);
		printf("%s\n", str);
		free(str);
	// rl_clear_history();
	}
	return 0;
}