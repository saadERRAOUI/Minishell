/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:04:14 by serraoui          #+#    #+#             */
/*   Updated: 2024/05/11 20:08:53 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static void	ft_cd_user(t_pwd *wds)
{
	char	*s;
	char	buffer[1024];

	s = ft_strjoin(ft_strdup("/Users/"), getenv("USER"));
	getcwd(buffer, sizeof(buffer));
	if (wds && wds->old_wd)
		free(wds->old_wd);
	wds->old_wd = ft_strdup(buffer);
	chdir(s);
	getcwd(buffer, sizeof(buffer));
	if (wds && wds->curr_wd)
		free(wds->curr_wd);
	wds->curr_wd = ft_strdup(buffer);
	free(s);
}

static void	ft_cd_error(char *s, int flag)
{
	s_exit = 1;
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(s, 2);
	if (!flag)
		ft_putstr_fd(": Not a directory\n", 2);
	else
		ft_putstr_fd(": No such file or directory\n", 2);
}

static void	ft_cd_access(t_pwd *wds, char *s)
{
	char	buffer[1024];

	getcwd(buffer, sizeof(buffer));
	if (wds && wds->old_wd)
		free(wds->old_wd);
	wds->old_wd = ft_strdup(buffer);
	chdir(s);
	getcwd(buffer, sizeof(buffer));
	if (wds && wds->curr_wd)
		free(wds->curr_wd);
	wds->curr_wd = ft_strdup(buffer);
}

static void	ft_cd_parent(t_pwd *wds)
{
	wds->curr_wd = ft_strjoin(wds->curr_wd, "/..");
	s_exit = 0;
	ft_putstr_fd("bash: cd: can't access parent directories\n", 2);
}

void	cd(char **av, t_pwd *wds)
{
	struct stat	path_stat;

	if (!av)
		return ;
	if (!av[1])
		ft_cd_user(wds);
	else if (stat(av[1], &path_stat) == 0
		&& S_ISREG(path_stat.st_mode)
	)
		ft_cd_error(av[1], 0);
	else if (((!ft_strcmp(av[1], "..") && wds && wds->old_wd
				&& ft_strnstr(wds->curr_wd,
					wds->old_wd,
					ft_strlen(wds->curr_wd)))
			|| (wds && !ft_strcmp(av[1], wds->old_wd)))
		&& access(wds->old_wd, F_OK) == -1
	)
		ft_cd_parent(wds);
	else if (!access(av[1], F_OK))
		ft_cd_access(wds, av[1]);
	else
		ft_cd_error(av[1], 1);
}
