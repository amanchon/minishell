/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**first_split_interpret_line(char *s)
{
	char	**dtab;
	int		i;
	int		j;

	dtab = ft_split(s, ";");
	free(s);
	i = -1;
	while (dtab[++i] != NULL)
	{
		j = 0;
		while (dtab[i][j] == ' ')
			j++;
		if (dtab[i][j] == '\0')
		{
			free_dtab(dtab);
			error_syntax(ft_strdup(";"));
			return (NULL);
		}
	}
	return (dtab);
}

int	interpret_line_quotes(char **s, int *i, int *quotes[2], char c)
{
	int	boo;

	boo = 0;
	while (s[0][*i] == c && *quotes[1] == 0)
	{
		*s = suppr_chr(*s, *i);
		boo = 1;
		if (s[0][*i] == c && (s[0][*i + 1] == '\0' || (s[0][*i + 1] == ' '
		&& *quotes[0] == 0) || s[0][*i + 1] == ';') && (*i == 0
		|| s[0][*i - 1] == ' ' || s[0][*i - 1] == ';'))
			s[0][*i] = '\xD0';
		else if (s[0][*i] == c)
			*s = suppr_chr(*s, *i);
		else
		{
			if (*quotes[0] == 0)
				*quotes[0] = 1;
			else
				*quotes[0] = 0;
		}
	}
	return (boo);
}

void	interpret_line_2(char **s, int *i, int *quote, int *dquote)
{
	int	boo;
	int	*quotes[2];

	boo = 0;
	quotes[0] = dquote;
	quotes[1] = quote;
	boo = interpret_line_quotes(s, i, quotes, '"');
	quotes[0] = quote;
	quotes[1] = dquote;
	boo = interpret_line_quotes(s, i, quotes, '\'');
	if (boo == 1)
		*i = *i - 1;
	else
		interpret_line_3(s, i, *quote, *dquote);
	return ;
}

void	interpret_line_boucle(char **s, int *i, int *quote, int *dquote)
{
	if (s[0][*i] == '\\' && (((s[0][*i + 1] == '\\' || ((s[0][*i + 1] == '|'
				|| s[0][*i + 1] == '>' || s[0][*i + 1] == '<'
				|| s[0][*i + 1] == ' ' || s[0][*i + 1] == ';'
				|| s[0][*i + 1] == '*' || s[0][*i + 1] == '~'
				|| s[0][*i + 1] == '$' || s[0][*i + 1] == '\''
				|| s[0][*i + 1] == '"')))
			&& *quote == 0 && *dquote == 0) || (s[0][*i + 1] == '"'
				&& *dquote == 1) || (s[0][*i + 1] == '\'' && *quote == 1)))
	{
		if (s[0][*i + 1] == ';' && *quote == 0 && *dquote == 0)
			s[0][*i + 1] = '\xC6';
		if (s[0][*i + 1] == ' ' && *quote == 0 && *dquote == 0)
			s[0][*i + 1] = '\xC7';
		s[0] = suppr_chr(*s, *i);
		return ;
	}
	else if ((s[0][*i] == '\\' && *quote == 0 && *dquote == 0)
		|| (s[0][*i] == '\\' && s[0][*i + 1] == '\\' && *dquote == 1))
		s[0] = suppr_chr(*s, *i);
	interpret_line_2(s, i, quote, dquote);
	return ;
}

char	**interpret_line(char *s)
{
	int		i;
	int		quote;
	int		dquote;
	char	**dtab;

	i = -1;
	quote = 0;
	dquote = 0;
	while (s[++i] != '\0')
	{
		interpret_line_boucle(&s, &i, &quote, &dquote);
		if (s == NULL)
			return (NULL);
		if (i >= 0 && s[i] == '\0')
			break ;
	}
	if (error_quote(quote, dquote, s) == 1)
		return (NULL);
	dtab = first_split_interpret_line(s);
	if (is_error_pipe(dtab) == -1)
		return (NULL);
	return (dtab);
}
