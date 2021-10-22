/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tab_to_spaces(char *key)
{
	key[0] = ' ';
	key[1] = ' ';
	key[2] = ' ';
	key[3] = ' ';
	key[4] = ' ';
	key[5] = ' ';
	key[6] = ' ';
	key[7] = ' ';
	key[8] = '\0';
	return ;
}

int	check_dim(t_coor dim_0, char **txt)
{
	t_coor	dim;

	dim = get_term_dimension();
	if (dim.y != dim_0.y || dim.x != dim_0.x)
	{
		tputs(tgetstr("cd", NULL), 1, ft_putchar_tty);
		ft_putstr_fd("\nminishell: dimension mise à jour !\n", 2);
		free(*txt);
		*txt = ft_strdup("");
		return (1);
	}
	return (0);
}

void	split_var_env2(char *s, int i, char **dest, t_env *env)
{
	char	*s2;

	s2 = ft_strdup(s);
	s2[i] = '\0';
	if (s[i] == '+' && s[i + 1] == '=')
	{
		if (get_env(s2, env) != NULL)
			dest[1] = ft_strmcatn(2, dest[1], ft_strdup(get_env(s2, env)));
		i++;
	}
	dest[0] = ft_strmcat(dest[0], s2);
	if (s[i] != '\0')
		dest[1] = ft_strmcatn(2, dest[1], ft_strdup(s2 + i + 1));
	free(s2);
	return ;
}

char	**split_var_env(char *s, t_env *env)
{
	int		i;
	char	**dest;

	i = 0;
	dest = malloc(8 * 3);
	if (dest == NULL)
		error_sys("malloc", -1);
	while (s[i] != '\0' && s[i] != '=' && (s[i] != '+' || s[i + 1] != '='))
		i++;
	dest[0] = ft_strdup("");
	if (s[i] == '\0')
		dest[1] = NULL;
	else
		dest[1] = ft_strdup("");
	dest[2] = NULL;
	if (i == 0)
		return (dest);
	split_var_env2(s, i, dest, env);
	return (dest);
}

char	**spe_split_joker(char **dtab, char *sep)
{
	int		i;
	char	*tmp;
	char	**dest;

	i = 0;
	tmp = ft_strdup("");
	while (dtab[i] != NULL)
	{
		tmp = ft_strmcat(tmp, dtab[i]);
		tmp = ft_strmcat(tmp, sep);
		i++;
	}
	free_dtab(dtab);
	dest = ft_split(tmp, sep);
	free(tmp);
	return (dest);
}
