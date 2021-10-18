/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_error_pipe(char **dtab)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	if (dtab == NULL)
		return (0);
	while (dtab[++i] != NULL)
	{
		j = -1;
		tmp = ft_split(dtab[i], " ");
		while (tmp[++j] != NULL)
		{
			if (ft_strcmp(tmp[j], "\xC8") == 0
				&& (j == 0 || tmp[j + 1] == NULL))
			{
				error_syntax(ft_strdup("|"));
				free_dtab(tmp);
				free_dtab(dtab);
				return (-1);
			}
		}
		free_dtab(tmp);
	}
	return (0);
}

int	ispipes(char **line, int n)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (line[i] != NULL)
	{
		if (ft_strcmp(line[i], "\xC8") == 0)
		{
			if (i == 0 || line[i + 1] == NULL)
			{
				if (n == 1)
					error_syntax(ft_strdup("|"));
				return (-1);
			}
			size++;
		}
		i++;
	}
	return (size);
}

char	***t_tab_pipes(char **line)
{
	int		size;
	int		i;
	int		j;
	char	***triple_tab;

	size = ispipes(line, 3);
	triple_tab = malloc(8 * (size + 2));
	if (triple_tab == NULL)
		error_sys("malloc", -1);
	i = -1;
	j = 0;
	while (j < size)
	{
		if (ft_strcmp(line[++i], "\xC8") == 0)
		{
			free(line[i]);
			line[i] = NULL;
			triple_tab[j++] = line;
			line = line + i + 1;
			i = -1;
		}
	}
	triple_tab[j] = line;
	triple_tab[j + 1] = NULL;
	return (triple_tab);
}
