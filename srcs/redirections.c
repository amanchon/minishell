/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	d_redirect_in_read(char *end, char **txt, t_env *env, t_coor dim_0)
{
	char	buf[256];
	int		rd;
	char	*line;
	t_coor	cursor_0;

	line = ft_strdup("");
	cursor_0 = get_cursor_pos();
	while (1)
	{
		rd = read(0, buf, 255);
		if (rd < 0)
			error_sys("read", errno);
		buf[rd] = '\0';
		if (buf[0] != '\n' && check_dim(dim_0, txt) > 0)
			break ;
		line = change_input(buf, line, &cursor_0, env);
		if (buf[0] == '\n' && buf[1] == '\0' && ft_strcmp(end, line) == 0)
			break ;
		if (buf[0] == '\n' && buf[1] == '\0')
			d_redi_nline(&line, txt, env, &cursor_0);
		if (buf[0] == (char)4 && line[0] == '\0')
			return (error_d_redirect(end));
	}
	free(line);
	return (0);
}

void	d_redirect_in(char *end, t_env *env, int *fd_in)
{
	int				pfd[2];
	struct termios	new_term;
	struct termios	old_term;
	char			*txt;
	t_coor			dim_0;

	if (*fd_in != 0)
		close(*fd_in);
	if (pipe(pfd) == -1)
		error_sys("pipe", errno);
	ft_putstr_fd("\033[1;32m", 2);
	ft_putstr_fd("> ", 2);
	ft_putstr_fd("\033[0m", 2);
	txt = ft_strdup("");
	get_term_attr(&new_term, &old_term);
	dim_0 = get_term_dimension();
	tcsetattr(0, TCSANOW, &new_term);
	d_redirect_in_read(end, &txt, env, dim_0);
	tcsetattr(0, TCSANOW, &old_term);
	write(pfd[1], txt, ft_strlen(txt));
	free(txt);
	close(pfd[1]);
	*fd_in = pfd[0];
	return ;
}

int	fd_redirection(char *line, int i, int *fd_in, int *fd_out)
{
	if (i < 3)
	{
		if (*fd_out != 1)
			close(*fd_out);
	}
	else
	{
		if (*fd_in != 0)
			close(*fd_in);
	}
	if (i == 1)
		*fd_out = open(line, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	else if (i == 2)
		*fd_out = open(line, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	else if (i == 3)
	{
		*fd_in = open(line, O_RDONLY);
		if (*fd_in < 0)
			return (error_fd(line, 1));
	}
	if (*fd_out < 0)
		return (error_fd(line, 0));
	return (0);
}

int	redirection2(char **line, int i, int *fd_in, int *fd_out)
{
	int	ret;

	ret = 0;
	if ((line[i][0] == '\xC9' || line[i][0] == '\xCA'
			|| line[i][0] == '\xCB' || line[i][0] == '\xCC')
		&& (line[i + 1] == NULL || line[i + 1][0] == '\xC8'
			|| line[i + 1][0] == '\xC9' || line[i + 1][0] == '\xCA'
			|| line[i + 1][0] == '\xCB' || line[i + 1][0] == '\xCC'))
	{
		error_syntax(ft_ctostr(1, line[i][0]));
		return (-2);
	}
	if (line[i][0] == '\xC9')
		ret = fd_redirection(line[i + 1], 1, fd_in, fd_out);
	else if (line[i][0] == '\xCA')
		ret = fd_redirection(line[i + 1], 2, fd_in, fd_out);
	else if (line[i][0] == '\xCB')
		ret = fd_redirection(line[i + 1], 3, fd_in, fd_out);
	return (ret);
}

int	redirections(char **line, int *fd_out, int *fd_in, t_env *env)
{
	int		i;
	int		fd_redi_out;
	int		ret;

	i = -1;
	ret = 0;
	while (line[++i] != NULL)
	{
		ret = redirection2(line, i, fd_in, fd_out);
		if (ret == -2)
			return (2);
		if (line[i][0] == '\xCC')
			d_redirect_in(line[i + 1], env, fd_in);
		if (ret != 0)
			break ;
		if (get_fd_redi_out(line, i, &fd_redi_out) == 1)
			return (1);
		dup2_n_close(*fd_out, fd_redi_out);
	}
	dup2_n_close(*fd_in, 0);
	redi_suppr_line(line);
	return (ret);
}
