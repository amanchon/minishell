/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_clef_env(char *s)
{
	int	i;

	i = 0;
	if (s == NULL || s[0] == '\0')
		return (1);
	if (s[0] == '-')
		return (2);
	while (s[i] != '\0')
	{
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
			|| (s[i] >= '0' && s[i] <= '9' && i > 0) || s[i] == '_')
			i = i * 1;
		else
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*get_env(char *s, t_env *env)
{
	t_env	*tmp;

	if (env == NULL)
		return (NULL);
	tmp = env;
	while (tmp->next != NULL && ft_strcmp(tmp->clef, s) != 0)
		tmp = tmp->next;
	if (tmp->next == NULL && ft_strcmp(tmp->clef, s) != 0)
		return (NULL);
	return (tmp->valeur);
}

void	see_env_write(t_env *tmp, int export)
{
	if (export == 1)
		ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(tmp->clef, 1);
	if (tmp->valeur != NULL)
	{
		ft_putchar_fd('=', 1);
		if (export == 1)
			ft_putstr_fd("\"", 1);
		if (ft_strcmp(tmp->clef, "_") == 0)
			ft_putstr_fd("env", 1);
		else
			ft_putstr_fd(tmp->valeur, 1);
		if (export == 1)
			ft_putstr_fd("\"", 1);
	}
	ft_putchar_fd('\n', 1);
	return ;
}

void	see_env(t_env *env, int export)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next != NULL)
	{
		if ((tmp->valeur != NULL || export == 1)
			&& (ft_strcmp(tmp->clef, "_") != 0 || export != 1))
			see_env_write(tmp, export);
		tmp = tmp->next;
	}
	if ((tmp->valeur != NULL || export == 1)
		&& (ft_strcmp(tmp->clef, "_") != 0 || export != 1))
		see_env_write(tmp, export);
	return ;
}
