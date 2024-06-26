/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:38:47 by amanchon          #+#    #+#             */
/*   Updated: 2020/01/16 19:24:21 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		totlen;
	int		i;
	int		k;

	i = -1;
	k = 0;
	if (!s1 || !s2)
		return (NULL);
	totlen = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	dest = malloc(sizeof(char) * (totlen + 1));
	if (dest == NULL)
		return (NULL);
	while (++i < totlen)
	{
		if (i < ft_strlen((char *)s1))
			dest[i] = s1[i];
		if (i >= ft_strlen((char *)s1) && (s2[k] != '\0'))
		{
			dest[i] = s2[k];
			k++;
		}
	}
	dest[totlen] = '\0';
	return (dest);
}
