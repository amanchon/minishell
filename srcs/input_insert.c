/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*key127(char *s, t_coor *cursor_0, t_coor cursor, int rpos)
{
	t_coor	dim;

	dim = get_term_dimension();
	move_cursor_left();
	if (rpos == ft_strlen(s))
	{
		tputs(tgetstr("dm", NULL), 1, ft_putchar_tty);
		s = suppr_chr(s, rpos - 1);
		tputs(tgetstr("dc", NULL), 1, ft_putchar_tty);
		tputs(tgetstr("ed", NULL), 1, ft_putchar_tty);
	}
	else
	{
		if (cursor.x == 0)
		{
			cursor.x = dim.x - 1;
			cursor.y -= 1;
		}
		else
			cursor.x -= 1;
		s = insert_del(s, cursor_0, cursor, rpos - 1);
	}
	return (s);
}

void	insert_boucle2(char *s, t_coor *cursor_0, t_coor *c_sav, t_coor dim)
{
	if ((ft_strlen(s) + cursor_0->x) % dim.x == 1
		&& cursor_0->y + (int)((ft_strlen(s) + cursor_0->x) / dim.x) == dim.y)
	{
		tputs(tgetstr("sf", NULL), 1, ft_putchar_tty);
		cursor_0->y = cursor_0->y - 1;
		c_sav->y = c_sav->y - 1;
		if (c_sav->y < dim.y - 1 - 1)
			tputs(tgetstr("do", NULL), 1, ft_putchar_tty);
	}
	else
		tputs(tgetstr("do", NULL), 1, ft_putchar_tty);
	return ;
}

t_coor	insert_boucle(char *s, t_coor *cursor_0, t_coor *cursor, t_coor dim)
{
	int		i;
	int		i_old;
	t_coor	c_sav;
	int		rpos;

	rpos = cursor->x - cursor_0->x + ((cursor->y - cursor_0->y) * dim.x);
	c_sav = *cursor;
	i = 0;
	if (ft_strlen(s) + cursor_0->x > dim.x)
		i = rpos + (dim.x - cursor->x);
	i_old = 0;
	while (ft_strlen(s) - rpos > dim.x - cursor->x)
	{
		insert_boucle2(s, cursor_0, &c_sav, dim);
		if (ft_strlen(s) + cursor_0->x - i_old - 1 != dim.x)
			tputs(tgetstr("ic", NULL), 1, ft_putchar_tty);
		write(0, &s[i], 1);
		i_old = i;
		i = i + dim.x;
		cursor->x = 1;
		if (cursor->y != dim.y - 1)
			cursor->y = cursor->y + 1;
		rpos = cursor->x - cursor_0->x + ((cursor->y - cursor_0->y) * dim.x);
	}
	return (c_sav);
}

char	*insert(char *key, char *s, t_coor *cursor_0, t_coor cursor)
{
	t_coor	c_sav;
	int		rpos;
	t_coor	dim;

	dim = get_term_dimension();
	rpos = cursor.x - cursor_0->x + ((cursor.y - cursor_0->y) * dim.x);
	c_sav = cursor;
	if (rpos < 0 || rpos > ft_strlen(s))
		return (s);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_tty);
	s = ft_insert_str(s, rpos, 0, ft_strdup(key));
	tputs(tgetstr("im", NULL), 1, ft_putchar_tty);
	tputs(tgetstr("ic", NULL), 1, ft_putchar_tty);
	write(0, key, 1);
	c_sav = insert_boucle(s, cursor_0, &cursor, dim);
	tputs(tgetstr("ei", NULL), 1, ft_putchar_tty);
	tputs(tgoto(tgetstr("cm", NULL), c_sav.x, c_sav.y), 1, ft_putchar_tty);
	move_cursor_right();
	tputs(tgetstr("ve", NULL), 1, ft_putchar_tty);
	return (s);
}

char	*insert_del(char *s, t_coor *cursor_0, t_coor cursor, int rpos)
{
	t_coor	c_sav;
	t_coor	dim;

	dim = get_term_dimension();
	c_sav = cursor;
	tputs(tgetstr("vi", NULL), 1, ft_putchar_tty);
	tputs(tgetstr("dm", NULL), 1, ft_putchar_tty);
	s = suppr_chr(s, rpos);
	tputs(tgetstr("dc", NULL), 1, ft_putchar_tty);
	while (ft_strlen(s) + 1 - rpos > dim.x - cursor.x)
	{
		tputs(tgoto(tgetstr("cm", NULL), dim.x - 1, cursor.y), 1,
			ft_putchar_tty);
		write(0, &s[rpos + dim.x - cursor.x - 1], 1);
		cursor.x = 0;
		cursor.y = cursor.y + 1;
		tputs(tgoto(tgetstr("cm", NULL), 0, cursor.y), 1, ft_putchar_tty);
		tputs(tgetstr("dc", NULL), 1, ft_putchar_tty);
		rpos = cursor.x - cursor_0->x + ((cursor.y - cursor_0->y) * dim.x);
	}
	tputs(tgoto(tgetstr("cm", NULL), c_sav.x, c_sav.y), 1, ft_putchar_tty);
	tputs(tgetstr("ed", NULL), 1, ft_putchar_tty);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_tty);
	return (s);
}
