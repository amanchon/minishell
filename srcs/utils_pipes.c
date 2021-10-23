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

void	t_tab_pipes2(char ***triple_tab, char **line, int *j, int *k)
{
	int		i;
	int		l;

	i = -1;
	l = 0;
	while (line[++i] != NULL)
	{
		if (ft_strcmp(line[i], "\xC8") == 0)
		{
			triple_tab[*j][++(*k)] = NULL;
			j = j + 1;
			*k = -1;
			while (line[i + l + 1] != NULL
				&& ft_strcmp(line[i + l + 1], "\xC8") != 0)
				l++;
			triple_tab[*j] = malloc(8 * (l + 1));
			if (triple_tab[*j] == NULL)
				error_sys("malloc", -1);
			l = 0;
		}
		else
			triple_tab[*j][++(*k)] = ft_strdup(line[i]);
	}
}

char	***t_tab_pipes(char **line, int size)
{
	int		j;
	int		k;
	char	***triple_tab;

	triple_tab = malloc(8 * (size + 2));
	if (triple_tab == NULL)
		error_sys("malloc", -1);
	j = 0;
	k = -1;
	while (ft_strcmp(line[j], "\xC8") != 0)
		j++;
	triple_tab[0] = malloc(8 * (j + 1));
	if (triple_tab[0] == NULL)
		error_sys("malloc", -1);
	j = 0;
	t_tab_pipes2(triple_tab, line, &j, &k);
	triple_tab[j][++k] = NULL;
	triple_tab[j + 1] = NULL;
	return (triple_tab);
}
