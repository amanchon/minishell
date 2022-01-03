/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo_arg(char **args, int i)
{
	int	j;

	j = 2;
	if (args[i] == NULL || (ft_strncmp(args[i], "-n", 2) != 0
			&& ft_strncmp(args[i], "/-n", 3) != 0
			&& ft_strncmp(args[i], "-/n", 3) != 0))
		return (0);
	while (args[i][j] == 'n')
		j++;
	if (args[i][j] == '\0')
		return (1);
	return (0);
}

int	ft_echo(char **args)
{
	int	i;

	i = 1;
	if (args[1] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	while (check_echo_arg(args, i) == 1)
		i++;
	if (args[i] != NULL)
		ft_putstr_fd(args[i++], 1);
	while (args[i] != NULL)
	{
		ft_putchar_fd(' ', 1);
		ft_putstr_fd(args[i], 1);
		i++;
	}
	if (check_echo_arg(args, 1) == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
