/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2020/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nblines(char *line, int nb)
{
	int	i;
	int	l;

	l = 0;
	i = nb;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			l++;
		i++;
	}
	return (l);
}

int	findfirstn(char **line, int opt_fill0)
{
	int	i;

	if (opt_fill0 >= 0)
	{
		while (opt_fill0 < ft_strlen(line[0]))
			line[0][opt_fill0++] = '\0';
		return (0);
	}
	i = 0;
	while (line[0][i] != '\0')
	{
		if (line[0][i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

int	ft_retval(int rd, int numline, char **mem)
{
	char	*tmp;

	if (rd == 0 && numline == 0)
	{
		free(*mem);
		*mem = NULL;
		return (0);
	}
	if (numline > 0)
	{
		tmp = ft_strdup(*mem + findfirstn(mem, -1) + 1);
		free(*mem);
		*mem = ft_strdup(tmp);
		free(tmp);
	}
	return (1);
}

int	ft_readline(char **mem, int fd)
{
	char	*buf;
	int		rd;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (-1);
	while (1)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd <= 0)
			break ;
		buf[rd] = '\0';
		*mem = ft_strmcat(*mem, buf);
		if (*mem == NULL)
			return (-1);
		if (nblines(*mem, 0) > 0)
			break ;
	}
	free(buf);
	return (rd);
}

int	get_next_line(const int fd, char **line)
{
	int			rd;
	static char	*mem[4200];
	int			i;
	char		b[1];

	rd = 0;
	if (!line || fd < 0 || BUFFER_SIZE < 1 || read(fd, b, 0) < 0)
		return (-1);
	*line = NULL;
	if (mem[fd] == NULL)
	{
		mem[fd] = ft_strdup("");
		if (mem[fd] == NULL)
			return (-1);
	}
	if (nblines(mem[fd], 0) == 0)
	{
		rd = ft_readline(&mem[fd], fd);
		if (rd < 0)
			return (-1);
	}
	*line = ft_strdup(mem[fd]);
	i = findfirstn(&mem[fd], -1);
	findfirstn(line, i);
	return (ft_retval(rd, nblines(mem[fd], 0), &mem[fd]));
}
