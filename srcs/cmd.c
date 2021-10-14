/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd_env(char **line, t_env *env)
{
	int	k;

	k = 0;
	if (ft_strcmp(line[0], "cd") == 0)
		cd(line, env);
	else if (ft_strcmp(line[0], "pwd:on") == 0)
		g_status_n_pid[2] = 1;
	else if (ft_strcmp(line[0], "pwd:off") == 0)
		g_status_n_pid[2] = 0;
	else if (ft_strcmp(line[0], "unset") == 0)
	{
		while (line[++k] != NULL)
			unset(line[k], env);
	}
	else if (ft_strcmp(line[0], "export") == 0)
	{
		while ((line[++k - 1] != NULL && line[k] != NULL) || k == 1)
			export(line[k], env);
	}
	else if (ft_strcmp(line[0], "exit") == 0)
		ft_exit(line, env);
	return ;
}

int	cmd_env(char **line, t_env *env)
{
	int	k;
	int	in_out_err[3];
	int	redi_in;
	int	redi_out;

	redi_in = 0;
	redi_out = 1;
	in_out_err[0] = dup(0);
	in_out_err[1] = dup(1);
	in_out_err[2] = dup(2);
	k = redirections(line, &redi_out, &redi_in, env);
	g_status_n_pid[0] = k;
	exec_cmd_env(line, env);
	dup2(in_out_err[0], 0);
	dup2(in_out_err[1], 1);
	dup2(in_out_err[2], 2);
	return (0);
}

int	cmd(char *cmd, char **line, t_env *env)
{
	char	buf[100];

	if (cmd == NULL)
		return (-1);
	if (ft_strcmp(cmd, "env") == 0)
		see_env(env, 0);
	else if (ft_strcmp(cmd, "pwd") == 0)
	{
		ft_putstr_fd(getcwd(buf, 100), 1);
		ft_putchar_fd('\n', 1);
	}
	else if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(line);
	else
		return (-1);
	return (0);
}
