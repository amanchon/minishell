/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset2(t_env *tmp, t_env *tmp2, char *s)
{
	while (tmp->next != NULL && ft_strcmp(tmp->next->clef, s) != 0)
		tmp = tmp->next;
	if (tmp->next == NULL && ft_strcmp(tmp->clef, s) != 0)
		return ;
	free(tmp->next->clef);
	if (tmp->next->valeur != NULL)
		free(tmp->next->valeur);
	tmp2 = tmp->next;
	tmp->next = tmp->next->next;
	free(tmp2);
	return ;
}

int	unset(char *s, t_env *env)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = env;
	tmp2 = env;
	if (s == NULL || s[0] == '\0' || check_clef_env(s) > 0)
	{
		error_cmd("unset", s, "identifiant non valide", check_clef_env(s));
		return (-1);
	}
	if (ft_strcmp(tmp->clef, s) == 0)
	{
		tmp2 = env->next;
		free(env->clef);
		if (env->valeur != NULL)
			free(env->valeur);
		*env = *tmp2;
		free(tmp2);
		return (0);
	}
	unset2(tmp, tmp2, s);
	return (0);
}

void	export2(char **var_env, t_env *env)
{
	t_env	*new;

	new = (struct s_env *)malloc(sizeof(struct s_env));
	if (new == NULL)
		error_sys("malloc", -1);
	unset(var_env[0], env);
	new->clef = ft_strdup(var_env[0]);
	new->valeur = ft_strdup(var_env[1]);
	new->next = NULL;
	free_dtab(var_env);
	while (env->next != NULL)
		env = env->next;
	env->next = new;
	return ;
}

int	export(char *s, t_env *env)
{
	char	**var_env;

	if (s == NULL || s[0] == '\0')
	{
		if (s == NULL)
			see_env(env, 1);
		else
			error_cmd("export", s, "identifiant non valide", 1);
		return (-1);
	}
	var_env = split_var_env(s, env);
	if (var_env == NULL || check_clef_env(var_env[0]) > 0)
	{
		if (var_env != NULL)
		{
			error_cmd("export", s, "identifiant non valide",
				check_clef_env(var_env[0]));
			free_dtab(var_env);
		}
		else
			error_cmd("export", s, "identifiant non valide", 1);
		return (-1);
	}
	export2(var_env, env);
	return (0);
}
