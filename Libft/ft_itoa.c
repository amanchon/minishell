/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:56:13 by amanchon          #+#    #+#             */
/*   Updated: 2020/01/16 16:56:42 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nbchar(int nbr)
{
	int	i;
	int	x;

	i = 0;
	x = nbr;
	if (x < 0)
		x = -x;
	while (x >= 10)
	{
		i++;
		x = x / 10;
	}
	i++;
	if (nbr < 0)
		i++;
	return (i);
}

int	ternaire_itoa(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		nchar;
	int		neg;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nchar = nbchar(n);
	dest = malloc(sizeof(char) * (nchar + 1));
	if (dest == NULL)
		return (NULL);
	neg = ternaire_itoa(n);
	if (n < 0)
	{
		n = n * -1;
		dest[0] = '-';
	}
	dest[nchar] = '\0';
	while (nchar > neg)
	{
		dest[nchar - 1] = (n % 10) + '0';
		n = n / 10;
		nchar--;
	}
	return (dest);
}
