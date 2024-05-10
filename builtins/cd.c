/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:04:14 by serraoui          #+#    #+#             */
/*   Updated: 2024/05/10 19:41:15 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	cd(char **av, t_pwd *wds)
{
	struct stat path_stat;
	char		*s;
    char	    buffer[1024];

    // printf("CURREN__ %s\n", buffer);
	if (!av)
		return ;
	if (!av[1])
	{
		s = ft_strjoin(ft_strdup("/Users/"), getenv("USER"));
		chdir(s);
		free(s);
	}
	else if (stat(av[1], &path_stat) == 0 && 
		S_ISREG(path_stat.st_mode))
		printf("bash: cd: %s: Not a directory\n", av[1]);
	else if ((!ft_strcmp(av[1], "..") || (wds && !ft_strcmp(av[1], wds->old_wd))) && access(wds->old_wd, F_OK) == -1)
    {
		printf("bash: cd: Can't access parent directories\n");
    }
	else if (!access(av[1], F_OK))
    {
        getcwd(buffer, sizeof(buffer));
        if (wds && wds->old_wd)
            free(wds->old_wd);
        wds->old_wd = ft_strdup(buffer);
		chdir(av[1]);
        getcwd(buffer, sizeof(buffer));
        if (wds && wds->curr_wd)
            free(wds->curr_wd);
        wds->curr_wd = ft_strdup(buffer);
    }
	else
	{
		s_exit = 1;
		printf("bash: cd: %s: No such file or directory\n", av[1]);
	}
}


// ./Users/serraoui/test/handler
// ./Users/serraoui