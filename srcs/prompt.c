/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	b[255];

	if (g_status_n_pid[2] != 1)
	{
		ft_putstr_fd("\033[1;32m", 2);
		write(2, "======> ", 8);
		ft_putstr_fd("\033[0m", 2);
		return ;
	}
	tputs(tgetstr("vi", NULL), 1, ft_putchar_tty);
	ft_putstr_fd("\033[1;32m", 2);
	write(2, "===", 3);
	ft_putstr_fd("\033[1;34m", 2);
	write(2, getcwd(b, 255), ft_strlen(getcwd(b, 255)));
	ft_putstr_fd("\033[1;32m", 2);
	write(2, "===> ", 5);
	ft_putstr_fd("\033[0m", 2);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_tty);
	return ;
}
