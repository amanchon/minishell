/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtabdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 18:10:30 by amanchon          #+#    #+#             */
/*   Updated: 2020/01/16 19:56:34 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dtabdup(char **src)
{
	char	**dest;
	int		i;

	i = 0;
	while (src[i] != NULL)
		i++;
	dest = (char **)malloc(8 * (i + 1));
	if (dest == NULL)
		return (NULL);
	i = -1;
	while (src[++i] != NULL)
		dest[i] = ft_strdup(src[i]);
	dest[i] = NULL;
	return (dest);
}
