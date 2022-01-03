/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit_string(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	is_cmd_env(char **line)
{
	if (line[0] == NULL)
		return (-1);
	if (ft_strcmp(line[0], "cd") == 0 || ft_strcmp(line[0], "pwd:on") == 0
		|| ft_strcmp(line[0], "pwd:off") == 0
		|| ft_strcmp(line[0], "unset") == 0
		|| ft_strcmp(line[0], "export") == 0 || ft_strcmp(line[0], "exit") == 0)
		return (0);
	else
		return (-1);
}

void	suppr_line_dtab(char **s, int n)
{
	free(s[n]);
	while (s[n + 1] != NULL)
	{
		s[n] = s[n + 1];
		n = n + 1;
	}
	s[n] = NULL;
}

char	*relative_to_absolute(char *r_path)
{
	char	*a_path;
	char	buf[255];

	a_path = ft_strmcatn(3, ft_strdup(getcwd(buf, 255)), ft_strdup("/"),
			ft_strdup(r_path));
	return (a_path);
}

int	check_input(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] < 32 || s[i] >= 127)
			return (0);
		i++;
	}
	return (1);
}
