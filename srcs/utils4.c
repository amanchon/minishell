/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putchar_tty(int c)
{
	int		fd;

	fd = open("/dev/tty", O_WRONLY);
	write(fd, &c, 1);
	close(fd);
	return (1);
}

t_coor	get_term_dimension(void)
{
	struct winsize	ws;
	t_coor			win;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	win.y = ws.ws_row;
	win.x = ws.ws_col;
	return (win);
}

t_coor	get_cursor_pos(void)
{
	t_coor	cursor;
	char	cursor_pos[17];
	int		rd;
	int		i;

	cursor.x = -1;
	cursor.y = -1;
	while (cursor.x < 0 || cursor.y < 0)
	{
		write(0, "\x1b[6n", 4);
		rd = read(0, cursor_pos, 16);
		if (rd < 0)
			error_sys("read", errno);
		cursor_pos[rd] = '\0';
		if (rd >= 6)
		{
			i = 2;
			cursor.y = ft_atoi(cursor_pos + i) - 1;
			while (ft_isdigit(cursor_pos[i]))
				i++;
			cursor.x = ft_atoi(cursor_pos + i + 1) - 1;
		}
	}
	return (cursor);
}

void	move_cursor_right(void)
{
	t_coor	cursor;
	t_coor	dim;

	dim = get_term_dimension();
	cursor = get_cursor_pos();
	if (cursor.x == dim.x - 1)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, cursor.y + 1), 1,
			ft_putchar_tty);
	}
	else
		tputs(tgetstr("nd", NULL), 1, ft_putchar_tty);
	return ;
}

void	move_cursor_left(void)
{
	t_coor	cursor;
	t_coor	dim;

	dim = get_term_dimension();
	cursor = get_cursor_pos();
	if (cursor.x == 0)
	{
		tputs(tgoto(tgetstr("cm", NULL), dim.x, cursor.y - 1), 1,
			ft_putchar_tty);
	}
	else
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar_tty);
	}
	return ;
}
