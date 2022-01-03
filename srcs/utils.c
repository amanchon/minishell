/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_term_attr(struct termios *new_term, struct termios *old_term)
{
	tcgetattr(0, old_term);
	tcgetattr(0, new_term);
	new_term->c_lflag &= ~(ICANON);
	new_term->c_lflag &= ~(ECHO);
	new_term->c_cc[VMIN] = 1;
	new_term->c_cc[VTIME] = 0;
	return ;
}

void	free_triple_tab(char ***t_tab)
{
	int	i;

	i = 0;
	while (t_tab[i] != NULL)
	{
		free_dtab(t_tab[i]);
		t_tab[i] = NULL;
		i++;
	}
	free(t_tab);
	t_tab = NULL;
	return ;
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env->next != NULL)
	{
		free(env->clef);
		if (env->valeur != NULL)
			free(env->valeur);
		tmp = env->next;
		free(env);
		env = tmp;
	}
	free(env->clef);
	if (env->valeur != NULL)
		free(env->valeur);
	free(env);
	return ;
}

char	*suppr_chr(char *s, int i)
{
	char	*s2;

	s[i] = '\0';
	s2 = ft_strdup(s + i + 1);
	s = ft_strmcat(s, s2);
	free(s2);
	return (s);
}

char	**list_to_dtab_env(t_env *env)
{
	char	*tab_env;
	char	**dtab_env;
	t_env	tmp;

	tmp = *env;
	tab_env = ft_strdup("");
	while (tmp.next != NULL)
	{
		if (tmp.valeur != NULL)
		{
			tab_env = ft_strmcatn(5, tab_env, ft_strdup(tmp.clef),
					ft_strdup("="), ft_strdup(tmp.valeur), ft_strdup("\n"));
		}
		tmp = *tmp.next;
	}
	dtab_env = ft_split(tab_env, "\n");
	free(tab_env);
	return (dtab_env);
}
