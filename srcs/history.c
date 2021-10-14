/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_history(char *path_h, char *new_hst, char *s, int gnl)
{
	int	fd;

	if (gnl < 0)
	{
		free(path_h);
		free(new_hst);
		return (-1);
	}
	fd = open(path_h, O_CREAT | O_TRUNC | O_RDWR | O_APPEND, S_IRWXU);
	if (fd < 0)
		return (-1);
	write(fd, new_hst, ft_strlen(new_hst));
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
	free(path_h);
	free(new_hst);
	close(fd);
	return (1);
}

int	fill_history(char *s, t_env *env)
{
	int		fd;
	int		gnl;
	char	*path_h;
	char	*hst;
	char	*new_hst;

	if (get_env("HOME", env) == NULL)
		return (-1);
	new_hst = ft_strdup("");
	path_h = ft_strmcat(ft_strdup(get_env("HOME", env)), "/.minishell_history");
	fd = open(path_h, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	while (1)
	{
		gnl = get_next_line(fd, &hst);
		if (gnl <= 0)
			break ;
		if (ft_strcmp(hst, s) != 0)
			new_hst = ft_strmcatn(3, new_hst, hst, ft_strdup("\n"));
		else
			free(hst);
	}
	free(hst);
	close(fd);
	write_history(path_h, new_hst, s, gnl);
	return (1);
}

char	*find_cmd(int *line_hst, int dir, char *s, char **hist)
{
	char	*dest;

	if (dir == 1)
	{
		while (--(*line_hst) >= 0)
		{
			if (ft_strncmp(hist[*line_hst], s, ft_strlen(s)) == 0)
			{
				dest = ft_strdup(hist[*line_hst]);
				break ;
			}
		}
	}
	if (dir == -1)
	{
		while (hist[++(*line_hst)] != NULL)
		{
			if (ft_strncmp(hist[*line_hst], s, ft_strlen(s)) == 0)
			{
				dest = ft_strdup(hist[*line_hst]);
				break ;
			}
		}
	}
	return (dest);
}

char	*find_cmd_history2(char *s, int dir, int *line_hst, char *hst)
{
	char	**hist;
	char	*dest;
	int		i;

	hist = ft_split(hst, "\n");
	free(hst);
	if (*line_hst == -1)
	{
		i = 0;
		while (hist[i] != NULL)
			i++;
		*line_hst = i;
	}
	dest = find_cmd(line_hst, dir, s, hist);
	if (*line_hst == -1 || hist[*line_hst] == NULL)
	{
		*line_hst = -1;
		free_dtab(hist);
		return (ft_strdup(s));
	}
	free_dtab(hist);
	if (*line_hst == 0)
		*line_hst = -7;
	return (dest);
}

char	*find_cmd_history(char *s, int dir, int *line_hst, t_env *env)
{
	int		fd;
	int		rd;
	char	*path_h;
	char	*hst;
	char	buf[1024];

	hst = ft_strdup("");
	if (*line_hst == -7)
		*line_hst = 0;
	path_h = ft_strmcat(ft_strdup(get_env("HOME", env)), "/.minishell_history");
	fd = open(path_h, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	free(path_h);
	while (1)
	{
		rd = read(fd, buf, 1023);
		if (rd <= 0)
			break ;
		buf[rd] = '\0';
		hst = ft_strmcat(hst, buf);
	}
	if (rd < 0)
		return (ft_strdup(s));
	close(fd);
	return (find_cmd_history2(s, dir, line_hst, hst));
}
