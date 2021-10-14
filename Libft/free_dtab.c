/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dtab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:56:47 by amanchon          #+#    #+#             */
/*   Updated: 2020/01/16 16:45:43 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_dtab(char **dtab)
{
	int	i;

	i = 0;
	while (dtab[i] != NULL)
	{
		free(dtab[i]);
		dtab[i] = NULL;
		i++;
	}
	free(dtab);
	dtab = NULL;
	return ;
}
