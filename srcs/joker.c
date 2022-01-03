/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joker.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_strcmp_joker(char *s_joker, char *name, int *i, int *j)
{
	int		n;
	int		boo;
	char	*sub;

	boo = 0;
	n = 0;
	while (s_joker[++(*i)] == '\xCD')
		boo = 1;
	while (s_joker[*i + n] != '\0' && s_joker[*i + n] != '\xCD')
		n++;
	if (n == 0)
		return (0);
	sub = ft_substr(s_joker, *i, n);
	while ((name[++(*j)] != '\0' && ft_strncmp(sub, name + *j, n) != 0)
		|| (s_joker[*i + n] == '\0' && s_joker[*i + n] != '\xCD'
			&& name[*j + n] != '\0'))
	{
		if (boo != 1)
		{
			free(sub);
			return (-1);
		}
	}
	free(sub);
	return (n);
}

int	strcmp_joker(char *name, char *s_joker)
{
	int		i;
	int		j;
	int		n;

	i = -1;
	j = -1;
	while (1)
	{
		n = init_strcmp_joker(s_joker, name, &i, &j);
		if (n <= 0)
			return (n);
		if (name[j] == '\0')
			return (-1);
		if (s_joker[i + n] == '\0' && s_joker[i + n] != '\xCD'
			&& name[j + n] == '\0')
			return (0);
		j = j - 1;
		i = i + n - 1;
	}
}

char	*find_files2(char **s_joker, char *dir_path, int i, struct dirent *file)
{
	char	*tmp;
	char	*dest;

	dest = ft_strdup("");
	if (s_joker[i + 1] == NULL)
	{
		dest = ft_strmcatn(4, dest, ft_strdup(dir_path + 2),
				ft_strdup(file->d_name), ft_strdup("\xD1"));
	}
	else if (file->d_type == 4)
	{
		tmp = ft_strmcat(ft_strdup(dir_path), file->d_name);
		dest = ft_strmcatn(2, dest, find_files(s_joker, tmp, i + 1));
	}
	return (dest);
}

char	*find_files(char **s_joker, char *dir_path, int i)
{
	DIR				*dir;
	struct dirent	*file;
	char			*dest;

	dest = ft_strdup("");
	dir = opendir(dir_path);
	dir_path = ft_strmcat(dir_path, "/");
	while (dir != NULL)
	{
		file = readdir(dir);
		if (file == NULL)
			break ;
		if ((ft_strchr(s_joker[i], '\xCD') == NULL
				|| (ft_strcmp(file->d_name, ".") != 0
					&& ft_strcmp(file->d_name, "..") != 0))
			&& strcmp_joker(file->d_name, s_joker[i]) == 0)
		{
			dest = ft_strmcatn(2, dest, find_files2(s_joker,
						dir_path, i, file));
		}
	}
	closedir(dir);
	free(dir_path);
	return (dest);
}

void	joker(char ***line)
{
	int		i;
	char	**dtab;
	char	*tmp;

	i = -1;
	while (line[0][++i] != NULL)
	{
		if (line[0][i][0] != '/' && ft_strchr(line[0][i], '\xCD') != NULL)
		{
			dtab = ft_split(line[0][i], "/");
			tmp = find_files(dtab, ft_strdup("."), 0);
			if (tmp[0] != '\0')
			{
				free(line[0][i]);
				tmp[ft_strlen(tmp) - 1] = '\0';
				line[0][i] = ft_strdup(tmp);
			}
			free(tmp);
			free_dtab(dtab);
		}
	}
	line[0] = spe_split_joker(line[0], "\xD1");
	return ;
}
