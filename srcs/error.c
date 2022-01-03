/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_d_redirect(char *end)
{
	ft_putstr_fd("minishell: avertissement, document délimité par la fin ", 2);
	ft_putstr_fd("du fichier (au lieu de « ", 2);
	ft_putstr_fd(end, 2);
	ft_putstr_fd(" »)\n", 2);
	g_status_n_pid[0] = 0;
	return (1);
}

void	error_syntax(char *symbol)
{
	if (symbol[0] == '\xC9')
		symbol[0] = '>';
	else if (symbol[0] == '\xCA')
	{
		symbol[0] = '>';
		symbol = ft_strmcatn(2, symbol, ft_ctostr(1, '>'));
	}
	else if (symbol[0] == '\xCB')
		symbol[0] = '<';
	else if (symbol[0] == '\xCC')
	{
		symbol[0] = '<';
		symbol = ft_strmcatn(2, symbol, ft_ctostr(1, '<'));
	}
	ft_putstr_fd("minishell: erreur de syntaxe près du symbole inattendu « ",
		2);
	ft_putstr_fd(symbol, 2);
	ft_putstr_fd(" »\n", 2);
	g_status_n_pid[0] = 2;
	free(symbol);
	return ;
}

void	error_exec2(char *cmd, int errnum)
{
	if (errnum == 13 || errnum == 8)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission non accordée\n", 2);
		g_status_n_pid[0] = 126;
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(strerror(errnum), 2);
		ft_putstr_fd("\n", 2);
		g_status_n_pid[0] = errnum;
	}
}

void	error_exec(char *cmd, int errnum)
{
	DIR	*dir;

	errno = 0;
	if (errnum == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": commande introuvable\n", 2);
		g_status_n_pid[0] = 127;
	}
	else
	{
		dir = opendir(cmd);
		if (dir != NULL || (errno != ENOTDIR && errno != 0))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": est un dossier\n", 2);
			g_status_n_pid[0] = 126;
			if (dir != NULL)
				closedir(dir);
		}
		else
			error_exec2(cmd, errnum);
	}
}

void	error_cmd(char *cmd, char *symbol, char *msg, int status)
{
	g_status_n_pid[0] = status;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": « ", 2);
	ft_putstr_fd(symbol, 2);
	ft_putstr_fd(" » : ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return ;
}
