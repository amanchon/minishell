/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_get_num2(char **line, long long j, int sign)
{
	unsigned long long	n;
	unsigned long long	max;

	n = 0;
	max = 9223372036854775807;
	while (ft_isdigit(line[1][j + n]) == 1 && (n < 20 || (n == 20
	&& line[1][j] == '0')))
		n++;
	j = j + n;
	if ((n == 20 && line[1][j] != '0') || n == 21)
		return (-1);
	n = ft_atoull(line[1] + j - n);
	while (line[1][j] == ' ')
		j++;
	if (line[1][j] != '\0')
		return (-1);
	if (n == 0)
		return (0);
	if ((n > max && sign == 1) || (n - 1 > max && sign == -1))
		return (-1);
	j = n * sign;
	j = j % (unsigned long long)256;
	return ((int)j);
}

int	ft_exit_get_num(char **line, t_env *env)
{
	long long			j;
	int					sign;

	j = 0;
	sign = 1;
	while (line[1][j] == ' ')
		j++;
	if (line[1][j] == '\0')
		error_exit(line, env);
	if (line[1][j] == '-' || line[1][j] == '+')
		j++;
	if (j != 0 && line[1][j - 1] == '-')
		sign = -1;
	if (ft_isdigit(line[1][j]) == 0)
		error_exit(line, env);
	while (line[1][j] == '0' && line[1][j + 1] == '0')
		j++;
	j = ft_exit_get_num2(line, j, sign);
	if (j == -1)
		error_exit(line, env);
	return ((int)j);
}

void	ft_exit(char **line, t_env *env)
{
	int	j;

	j = 0;
	ft_putstr_fd("exit\n", 2);
	if (line[1] != NULL)
		j = ft_exit_get_num(line, env);
	if (line[1] != NULL && line[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: trop d'arguments\n", 2);
		g_status_n_pid[0] = 1;
		return ;
	}
	exit(j);
}
