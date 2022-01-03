/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_minishell2(pid_t pid, int signum)
{
	if (kill(pid, signum) == 0)
	{
		if (signum == SIGQUIT)
			ft_putstr_fd("Quitter: 3\n", 1);
		if (signum == SIGINT)
			ft_putstr_fd("\n", 1);
	}
	return ;
}

void	signal_minishell(int signum)
{
	pid_t	pid;

	pid = (g_status_n_pid[1]);
	g_status_n_pid[0] = 128 + signum;
	if (pid == -10)
	{
		if (signum == SIGINT)
		{
			tputs(tgetstr("cd", NULL), 1, ft_putchar_tty);
			ft_putstr_fd("^C\n", 1);
			g_status_n_pid[0] = 386;
			prompt();
		}
	}
	else if (pid == 0)
	{
		if (signum == SIGINT)
		{
			tputs(tgetstr("cd", NULL), 1, ft_putchar_tty);
			ft_putstr_fd("^C\n", 1);
			exit(130);
		}
	}
	else
		signal_minishell2(pid, signum);
}
