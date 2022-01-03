/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctostr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 19:54:09 by yotillar          #+#    #+#             */
/*   Updated: 2021/03/03 04:47:21 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ctostr(int size, char c)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * (size + 1));
	if (dest == NULL || size < 0)
		return (0);
	while (i < size)
	{
		dest[i] = c;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
