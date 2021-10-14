/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*print_n_write_key(char *s, char *key, t_coor *c_0, t_coor c)
{
	t_coor	d;

	d = get_term_dimension();
	if (key[0] == '\n' || c.x - c_0->x + ((c.y - c_0->y) * d.x) == ft_strlen(s))
	{
		if (key[0] == '\n')
		{
			tputs(tgoto(tgetstr("cm", NULL), (c_0->x + ft_strlen(s)) % d.x,
					c_0->y + (c_0->x + ft_strlen(s) / d.x)), 1, ft_putchar_tty);
			write(0, key, 1);
			return (s);
		}
		write(0, key, ft_strlen(key));
		if (c.x == d.x - 1)
		{
			tputs(tgetstr("do", NULL), 1, ft_putchar_tty);
			if (c.y == d.y - 1)
				c_0->y = c_0->y - 1;
		}
		s = ft_strmcat(s, key);
	}
	else if (ft_strlen(key) == 1)
		s = insert(key, s, c_0, c);
	return (s);
}

void	change_input2(char *key, char **s, t_coor *cursor_0)
{
	t_coor	dim;
	t_coor	cursor;
	int		rpos;
	int		size;

	size = ft_strlen(*s);
	cursor = get_cursor_pos();
	dim = get_term_dimension();
	rpos = cursor.x - cursor_0->x + ((cursor.y - cursor_0->y) * dim.x);
	if (check_input(key) == 1 || (key[0] == '\n' && key[1] == '\0'))
		*s = print_n_write_key(*s, key, cursor_0, cursor);
	else if (key[0] == 27 && (key[1] == 91) && key[2] == 51 && key[3] == 126
		&& key[4] == 0 && rpos < size && rpos <= size)
		*s = insert_del(*s, cursor_0, cursor, rpos);
	else if (key[0] == 27 && (key[1] == 91 || key[1] == 79) && key[2] == 67
		&& key[3] == 0 && rpos < size)
		move_cursor_right();
	else if (key[0] == 27 && (key[1] == 91 || key[1] == 79) && key[2] == 68
		&& key[3] == 0 && rpos > 0)
		move_cursor_left();
	else if (key[0] == 127 && key[1] == 0 && rpos > 0 && rpos <= size)
		*s = key127(*s, cursor_0, cursor, rpos);
	return ;
}

char	*set_staticvar_history(char *s, char *real_s, int *line_hst, char *key)
{
	if (s != NULL)
	{
		if (!(*line_hst) && *line_hst != -7)
			*line_hst = -1;
		if (s[0] == '\0' && real_s != NULL)
		{
			free(real_s);
			real_s = NULL;
		}
		if (real_s == NULL)
			real_s = ft_strdup(s);
		return (real_s);
	}
	else if (!(key[0] == 27 && (key[1] == 91 || key[1] == 79) && (key[2] == 65
				|| key[2] == 66 || key[2] == 67 || key[2] == 68)
			&& key[3] == 0))
	{
		free(real_s);
		if (key[0] == '\n')
			real_s = NULL;
		else
			real_s = ft_strdup(s);
		*line_hst = -1;
	}
	return (real_s);
}

char	*get_up_history(char *real_s, int *l_hst, t_coor *c_0, t_env *env)
{
	t_coor	dim;
	int		size;
	char	*s;

	dim = get_term_dimension();
	s = find_cmd_history(real_s, 1, l_hst, env);
	tputs(tgoto(tgetstr("cm", NULL), c_0->x, c_0->y), 1, ft_putchar_tty);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_tty);
	size = ft_strlen(s);
	write(0, s, size);
	if (c_0->y > dim.y - 1 - ((size + c_0->x) / dim.x))
		c_0->y = dim.y - 1 - ((size + c_0->x) / dim.x);
	return (s);
}

char	*change_input(char *key, char *s, t_coor *c_0, t_env *env)
{
	static char	*real_str;
	static int	line_hst;

	real_str = set_staticvar_history(s, real_str, &line_hst, "");
	if (key[0] == 27 && (key[1] == 91 || key[1] == 79) && key[2] == 65
		&& key[3] == 0 && get_env("HOME", env) != NULL)
	{
		free(s);
		s = get_up_history(real_str, &line_hst, c_0, env);
	}
	else if (key[0] == 27 && (key[1] == 91 || key[1] == 79) && key[2] == 66
		&& key[3] == 0 && line_hst > -1 && get_env("HOME", env) != NULL)
	{
		free(s);
		s = find_cmd_history(real_str, -1, &line_hst, env);
		tputs(tgoto(tgetstr("cm", NULL), c_0->x, c_0->y), 1, ft_putchar_tty);
		tputs(tgetstr("cd", NULL), 1, ft_putchar_tty);
		write(0, s, ft_strlen(s));
	}
	else
		change_input2(key, &s, c_0);
	real_str = set_staticvar_history(NULL, real_str, &line_hst, key);
	return (s);
}
