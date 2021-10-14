/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	d_redi_nline(char **line, char **txt, t_env *env, t_coor *cursor_0)
{
	*line = replace_var_spe_redi(*line, env);
	*txt = ft_strmcatn(3, *txt, *line, ft_strdup("\n"));
	*line = ft_strdup("");
	ft_putstr_fd("\033[1;32m", 2);
	ft_putstr_fd("> ", 2);
	ft_putstr_fd("\033[0m", 2);
	*cursor_0 = get_cursor_pos();
	return ;
}

int	dup2_n_close(int fd1, int fd2)
{
	if (fd1 != fd2)
	{
		dup2(fd1, fd2);
		close(fd1);
		return (1);
	}
	return (0);
}

void	redi_suppr_line(char **line)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
	{
		if (line[i][0] == '\xC9' || line[i][0] == '\xCA' || line[i][0] == '\xCB'
		|| line[i][0] == '\xCC')
		{
			suppr_line_dtab(line, i + 1);
			suppr_line_dtab(line, i);
		}
		else
			i++;
	}
	if (line[0] == NULL)
		line[0] = ft_strdup("");
	return ;
}

int	get_fd_redi_out(char **line, int i, int *fd_redi_out)
{
	*fd_redi_out = 1;
	if ((line[i][0] == '\xC9' || line[i][0] == '\xCA') &&
	ft_isdigit(line[i][1]) == 1)
		*fd_redi_out = ft_atoi(line[i] + 1);
	if (*fd_redi_out > 1023)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putnbr_fd(*fd_redi_out, 2);
		ft_putstr_fd(": Mauvais descripteur de fichier\n", 2);
		return (1);
	}
	return (0);
}
