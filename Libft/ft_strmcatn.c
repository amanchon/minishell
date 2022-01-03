/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmcatn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 23:07:34 by amanchon          #+#    #+#             */
/*   Updated: 2020/11/21 18:56:55 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmcatn(int n, char *s1, char *s2, ...)
{
	int		i;
	va_list	vl;
	char	*dest;
	char	*add;

	i = 2;
	va_start(vl, s2);
	dest = ft_strmcat(s1, s2);
	if (dest == NULL)
		return (NULL);
	free(s2);
	s2 = NULL;
	while (i < n)
	{
		add = va_arg(vl, char *);
		dest = ft_strmcat(dest, add);
		i++;
		free(add);
		add = NULL;
	}
	va_end(vl);
	return (dest);
}
