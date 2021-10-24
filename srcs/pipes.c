/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipe(char **line, t_env *env)
{
	if (is_cmd_env(line) != -1)
	{
		cmd_env(line, env, NULL);
		free_all(line, env, NULL);
	}
	else if (g_status_n_pid[0] != 0)
	{
		free_all(line, env, NULL);
	}
	else if (cmd(line[0], line, env) == -1)
	{
		exec_instruction(line[0], line, env);
	}
	exit(g_status_n_pid[0]);
}

void	pipe_exec_n_wait(char ***line_pipe, int i, t_env *env)
{
	char	**line;
	int		status;
	int		waiit;

	if (g_status_n_pid[1] == 0)
	{
		line = ft_dtabdup(line_pipe[i]);
		free_triple_tab(line_pipe);
		if (line == NULL)
			error_sys("malloc", -1);
		exec_pipe(line, env);
	}
	waiit = waitpid(g_status_n_pid[1], &status, 0);
	if (WIFEXITED(status))
		g_status_n_pid[0] = WEXITSTATUS(status);
	while (1)
	{
		waiit = wait(&status);
		if (waiit < 0)
			break ;
	}
	free_env(env);
	return ;
}

void	pipe_close_fd(int *fdd, int pfd[2], int in_out_err[3])
{
	if (g_status_n_pid[1] == 0)
		close(pfd[0]);
	if (g_status_n_pid[1] > 0)
	{
		close(*fdd);
		close(pfd[1]);
		*fdd = pfd[0];
		dup2(in_out_err[0], 0);
		dup2(in_out_err[1], 1);
		dup2(in_out_err[2], 2);
	}
	return ;
}

void	pipe_open_fd(char ***line_pip, int pfd[2], int fdd, t_env *env)
{
	int		redi_in;
	int		redi_out;

	redi_in = 0;
	redi_out = 1;
	if (is_cmd_env(line_pip[0]) == -1)
		g_status_n_pid[0] = redirections(line_pip[0], &redi_out, &redi_in, env);
	if (line_pip[1] != NULL && redi_out == 1)
		dup2(pfd[1], 1);
	if (fdd != 0 && redi_in == 0)
		dup2(fdd, 0);
	return ;
}

void	pipes(char **line, t_env *env, int i)
{
	int		pfd[2];
	int		fdd;
	char	***line_pipe;
	int		in_out_err[3];

	in_out_err[0] = dup(0);
	in_out_err[1] = dup(1);
	in_out_err[2] = dup(2);
	line_pipe = t_tab_pipes(line, ispipes(line, 3));
	free_dtab(line);
	fdd = 0;
	while (g_status_n_pid[1] != 0 && line_pipe[++i] != NULL)
	{
		g_status_n_pid[1] = 0;
		if (pipe(pfd) == -1)
			error_sys("pipe", errno);
		pipe_open_fd(line_pipe + i, pfd, fdd, env);
		g_status_n_pid[1] = (int)fork();
		if (g_status_n_pid[1] < 0)
			error_sys("fork", errno);
		pipe_close_fd(&fdd, pfd, in_out_err);
	}
	pipe_exec_n_wait(line_pipe, i, env);
	free_triple_tab(line_pipe);
}
