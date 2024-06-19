/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checknfill_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_needed_var(t_env *dest, int option)
{
	char	*s_export;

	if (option == 0)
		s_export = ft_strdup("TERM=xterm-256color");
	if (option == 1)
		s_export = ft_strdup("SHLVL=1");
	if (option == 2)
		s_export = ft_strdup("PATH=/bin:usr/bin");
	export(s_export, dest);
	free(s_export);
	return ;
}

t_env	*make_env(char *name)
{
	t_env	*dest;
	t_env	*first;
	char	buf[100];
	char	*term;

	dest = (struct s_env *)malloc(sizeof(struct s_env));
	if (dest == NULL)
		error_sys("malloc", -1);
	dest->clef = ft_strdup("PWD");
	dest->valeur = ft_strdup(getcwd(buf, 100));
	dest->next = NULL;
	first = (struct s_env *)malloc(sizeof(struct s_env));
	if (first == NULL)
		error_sys("malloc", -1);
	first->clef = ft_strdup("PATH");
	first->valeur = ft_strdup("/bin:usr/bin");
	first->next = dest;
	export_needed_var(dest, 0);
	export_needed_var(dest, 1);
	term = ft_strmcatn(4, ft_strdup("_="), ft_strdup(get_env("PWD", dest)),
			ft_strdup("/"), ft_strdup(name));
	export(term, dest);
	free(term);
	return (first);
}

t_env	*fill_env_next(t_env *first, char **env, int i)
{
	t_env	*dest;
	char	**var_env;
	char	*s_export;
	char	buf[100];

	while (--i >= 0)
	{
		dest = (struct s_env *)malloc(sizeof(struct s_env));
		var_env = split_var_env(env[i], NULL);
		if (dest == NULL || var_env == NULL)
			error_sys("malloc", -1);
		dest->clef = var_env[0];
		dest->valeur = var_env[1];
		dest->next = first;
		first = dest;
		free(var_env);
	}
	if (get_env("PATH", dest) == NULL)
		export_needed_var(first, 2);
	s_export = ft_strmcat(ft_strdup("PWD="), getcwd(buf, 100));
	if (get_env("PWD", dest) == NULL)
		export(s_export, dest);
	free(s_export);
	return (dest);
}

void	fill_env_needed(t_env *first, char *name)
{
	char	*s_export;

	if (get_env("TERM", first) == NULL)
		export_needed_var(first, 0);
	s_export = ft_strmcatn(4, ft_strdup("_="), ft_strdup(get_env("PWD", first)),
			ft_strdup("/"), ft_strdup(name));
	if (get_env("_", first) == NULL)
		export(s_export, first);
	free(s_export);
	if (get_env("SHLVL", first) == NULL
		|| ft_isdigit_string(get_env("SHLVL", first)) == 0)
		export_needed_var(first, 1);
	else
	{
		s_export = ft_strmcatn(2, ft_strdup("SHLVL="),
				ft_itoa(ft_atoi(get_env("SHLVL", first)) + 1));
		export(s_export, first);
		free(s_export);
	}
	return ;
}

t_env	*fill_env(char **env, char *name)
{
	int		i;
	char	**var_env;
	t_env	*first;

	i = 0;
	if (env == NULL || env[0] == NULL || (env[0][0] == '_' && env[1] == NULL))
		return (make_env(name));
	while (env[i] != NULL)
		i++;
	i--;
	first = (struct s_env *)malloc(sizeof(struct s_env));
	var_env = split_var_env(env[i], NULL);
	if (first == NULL || var_env == NULL)
		error_sys("malloc", -1);
	first->clef = var_env[0];
	first->valeur = var_env[1];
	first->next = NULL;
	free(var_env);
	first = fill_env_next(first, env, i);
	if (first == NULL)
		error_sys("malloc", -1);
	fill_env_needed(first, name);
	return (first);
}
