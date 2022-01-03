/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error(char *s, char *tmp)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": Aucun dossier de ce type\n", 2);
	g_status_n_pid[0] = 1;
	free(s);
	free(tmp);
	return ;
}

int	cd_check_nb_args(char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: cd: trop d'arguments\n", 2);
		g_status_n_pid[0] = 1;
	}
	return (i);
}

char	*cd_option(int i, char *path, t_env *env)
{
	char	*s;

	if (i == 1)
	{
		s = ft_strdup(get_env("HOME", env));
		if (s == NULL)
		{
			ft_putstr_fd("minishell: cd: « HOME » non défini\n", 2);
			g_status_n_pid[0] = 1;
			return (NULL);
		}
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		s = ft_strdup(get_env("OLDPWD", env));
		if (s == NULL)
		{
			ft_putstr_fd("minishell: cd: « OLDPWD » non défini\n", 2);
			g_status_n_pid[0] = 1;
			return (NULL);
		}
	}
	else
		s = ft_strdup(path);
	return (s);
}

void	cd(char **path, t_env *env)
{
	char	*s;
	char	*tmp;
	char	b[255];

	if (cd_check_nb_args(path) > 2)
		return ;
	s = cd_option(cd_check_nb_args(path), path[1], env);
	if (s == NULL)
		return ;
	if (get_env("PWD", env) != NULL)
		tmp = ft_strmcat(ft_strdup("OLDPWD="), get_env("PWD", env));
	else
		tmp = ft_strdup("OLDPWD=");
	if (s[0] != '\0' && chdir(s) == -1)
	{
		cd_error(s, tmp);
		return ;
	}
	free(s);
	export(tmp, env);
	free(tmp);
	s = ft_strmcat(ft_strdup("PWD="), getcwd(b, 255));
	export(s, env);
	free(s);
}
