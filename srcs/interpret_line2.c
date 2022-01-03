/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_line2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	normalize_dtab(char **t_tab, int j)
{
	int	i;
	int	k;

	i = 0;
	while (t_tab[i] != NULL)
	{
		k = 0;
		while (t_tab[i][k] != '\0')
		{
			if (t_tab[i][k] == '\xC7')
				t_tab[i][k] = ' ';
			else if (t_tab[i][k] == '\xC6')
				t_tab[i][k] = ';';
			else if (t_tab[i][k] == '\xCD' && j == 1)
				t_tab[i][k] = '*';
			else if (t_tab[i][k] == '\xD0' && j == 1)
				t_tab[i][k] = '\0';
			k++;
		}
		i++;
	}
	return ;
}

void	interpret_fd_redi_out(char **s, int *i, char c)
{
	int		j;
	int		n;

	j = *i;
	while (j != 0 && ft_isdigit(s[0][j - 1]) == 1)
		j = j - 1;
	if (*i != j && (j == 0 || s[0][j - 1] == ' ' || s[0][j - 1] == ';'))
	{
		n = ft_atoi(s[0] + j);
		*s = ft_insert_str(*s, *i + 2, 0, ft_itoa(n));
		n = *i - j;
		while (n > 0)
		{
			*s = suppr_chr(*s, j);
			n = n - 1;
		}
		s[0][*i - (*i - j) + 1] = c;
		*i = *i + 2;
		return ;
	}
	s[0][*i + 1] = c;
	*i = *i + 2;
	return ;
}

void	interpret_line_redirect(char **s, int *i, int quote, int dquote)
{
	if (s[0][*i] == '<' && s[0][*i + 1] == '<' && dquote == 0 && quote == 0)
	{
		*s = ft_insert_str(*s, *i, 2, ft_strdup(" < "));
		s[0][*i + 1] = '\xCC';
		*i = *i + 2;
	}
	if (s[0][*i] == '<' && dquote == 0 && quote == 0)
	{
		*s = ft_insert_str(*s, *i, 1, ft_strdup(" < "));
		s[0][*i + 1] = '\xCB';
		*i = *i + 2;
	}
	if (s[0][*i] == '>' && s[0][*i + 1] == '>' && dquote == 0 && quote == 0)
	{
		*s = ft_insert_str(*s, *i, 2, ft_strdup(" > "));
		interpret_fd_redi_out(s, i, '\xCA');
	}
	if (s[0][*i] == '>' && dquote == 0 && quote == 0)
	{
		*s = ft_insert_str(*s, *i, 1, ft_strdup(" > "));
		interpret_fd_redi_out(s, i, '\xC9');
	}
	if (s[0][*i] == '*' && dquote == 0 && quote == 0)
		s[0][*i++] = '\xCD';
	return ;
}

void	interpret_line_3(char **s, int *i, int quote, int dquote)
{
	interpret_line_redirect(s, i, quote, dquote);
	if (s[0][*i] == '|' && dquote == 0 && quote == 0)
	{
		*s = ft_insert_str(*s, *i, 1, ft_strdup(" | "));
		s[0][*i + 1] = '\xC8';
		*i = *i + 2;
	}
	if (s[0][*i] == ' ' && (dquote == 1 || quote == 1))
		s[0][*i] = '\xC7';
	if (s[0][*i] == ';' && (s[0][*i + 1] == ';' || *i == 0)
		&& dquote == 0 && quote == 0)
	{
		free(s[0]);
		s[0] = NULL;
		error_syntax(ft_strdup(";"));
		return ;
	}
	if (s[0][*i] == ';' && (dquote == 1 || quote == 1))
		s[0][*i] = '\xC6';
	mark_var(s, i, quote, dquote);
	mark_tilde(s, i, quote, dquote);
	return ;
}
