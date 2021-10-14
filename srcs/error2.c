/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_quote(int quote, int dquote, char *s)
{
	if (quote == 1 || dquote == 1)
	{
		ft_putstr_fd("minishell: fin de fichier (EOF) prématurée lors de ", 2);
		if (quote == 1)
			ft_putstr_fd("la recherche du « ' » correspondant\n", 2);
		else
			ft_putstr_fd("la recherche du « \" » correspondant\n", 2);
		g_status_n_pid[0] = 1;
		free(s);
		return (1);
	}
	return (0);
}

int	error_fd(char *line, int permission)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(line, 2);
	if (permission == 1)
		ft_putstr_fd(": Aucun fichier ou dossier de ce type\n", 2);
	else
		ft_putstr_fd(": Permission non accordée\n", 2);
	return (1);
}

inline	void	error_sys(char *line, int errnum)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd(" a échoué", 2);
	if (errnum == -1)
	{
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	ft_putstr_fd(", errno renvoyé !\n", 2);
	ft_putstr_fd("strerror: ", 2);
	ft_putstr_fd(strerror(errnum), 2);
	ft_putstr_fd("\n", 2);
	exit(errnum);
}
