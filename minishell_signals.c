/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serraoui <serraoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:41:59 by serraoui          #+#    #+#             */
/*   Updated: 2024/05/12 17:22:57 by serraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        g_exit = 1;
        write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
    else if (sig == SIGQUIT)
        rl_redisplay();
}

void    child_exit(int status)
{
    if (WIFEXITED(status))
        g_exit = WEXITSTATUS(status);
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
    {
        g_exit = 131;
        ft_putstr_fd("Quit: 3\n", 2);
    }
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
        g_exit = 130;
}

void    child_signal_def(int flag)
{
    if (!flag)
    {
        signal(SIGQUIT, signal_handler);
        signal(SIGINT, signal_handler);
    }
    else if (flag == 1)
    {
        signal(SIGQUIT, SIG_DFL);
        signal(SIGINT, SIG_DFL);
    }
    else if (flag == 2)
    {
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, SIG_IGN);
    }
    else if (flag == 3)
    {
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, SIG_DFL);
    }
}