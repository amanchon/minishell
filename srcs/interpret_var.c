/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_var(char *s, int *i, t_env *env)
{
	char	*dest;

	*i = 0;
	while (s[*i] != '\0' && s[*i] != '\xCE' && s[*i] != '\xD1')
		*i = *i + 1;
	s[*i] = '\0';
	if (ft_strcmp("?", s) == 0)
		dest = ft_itoa(g_status_n_pid[0]);
	else
		dest = ft_strdup(get_env(s, env));
	free(s);
	*i = *i + 1;
	if (dest == NULL)
		return (ft_strdup(""));
	return (dest);
}

char	*replace_var2(char *line, int i, t_env *env, int type)
{
	int		k;
	char	*var;
	char	*dest;
	int		j;

	if (type == 1)
	{
		var = ft_strdup(get_env("HOME", env));
		if (var == NULL)
			var = ft_strdup("");
		k = 0;
	}
	else
		var = search_var(ft_strdup(line + i + 1), &k, env);
	j = -1;
	while (type == 2 && var[++j] != '\0')
	{
		if (var[j] == ' ')
			var[j] = '\xC7';
	}
	line[i] = '\0';
	dest = ft_strmcatn(3, ft_strdup(line), var, ft_strdup(line + i + k + 1));
	return (dest);
}

char	*replace_var(char *line, t_env *env)
{
	int		i;
	char	*dest;

	i = 0;
	while (1)
	{
		while (line[i] != '\0' && line[i] != '\xCE' && line[i] != '\xD1'
			&& line[i] != '\xCF')
			i++;
		if (line[i] == '\0')
			break ;
		if (line[i] == '\xCF')
			dest = replace_var2(line, i, env, 1);
		else if (line[i] == '\xCE')
			dest = replace_var2(line, i, env, 0);
		else if (line[i] == '\xD1')
			dest = replace_var2(line, i, env, 2);
		free(line);
		line = dest;
	}
	return (line);
}

char	*replace_var_spe_redi(char *s, t_env *env)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == '\\' && (s[i + 1] == '\\' || s[i + 1] == '$'))
			s = suppr_chr(s, i);
		else
			mark_var(&s, &i, 0, 0);
	}
	return (replace_var(s, env));
}
