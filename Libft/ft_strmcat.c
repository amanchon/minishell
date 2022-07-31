/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 01:51:54 by amanchon          #+#    #+#             */
/*   Updated: 2020/03/04 02:25:23 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmcat(char *src, char *add)
{
	char	*dest;
	int		i;
	int		j;
	int		size;

	if (!src || !add)
		return (NULL);
	size = ft_strlen(src) + ft_strlen(add);
	i = -1;
	j = 0;
	dest = malloc(sizeof(char) * (size + 1));
	if (dest == NULL)
		return (NULL);
	while (src[++i] != '\0')
		dest[i] = src[i];
	while (add[j] != '\0')
	{
		dest[i] = add[j];
		i++;
		j++;
	}
	dest[size] = '\0';
	free(src);
	src = NULL;
	return (dest);
}

