/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_n_treat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dim_n_status(t_coor *cursor_0, t_coor *dim_0, char **s)
{
	if (check_dim(*dim_0, s) > 0)
		return (1);
	if (g_status_n_pid[0] == 386)
	{
		free(*s);
		*s = ft_strdup("");
		*cursor_0 = get_cursor_pos();
		*dim_0 = get_term_dimension();
		g_status_n_pid[0] = 130;
	}
	return (0);
}

char	*read_instruction_line(t_env *env, t_coor *cursor_0)
{
	char	buf[256];
	char	*s;
	int		rd;
	t_coor	dim_0;

	dim_0 = get_term_dimension();
	s = ft_strdup("");
	while (1)
	{
		rd = read(0, buf, 255);
		if (rd < 0)
			error_sys("read", errno);
		if ((int)(buf[0]) == 4 && ft_strlen(s) == 0)
		{
			ft_putstr_fd("exit\n", 2);
			free_env(env);
			free(s);
			exit(0);
		}
		if (check_dim_n_status(cursor_0, &dim_0, &s) > 0)
			return (s);
		buf[rd] = '\0';
		s = change_input(buf, s, cursor_0, env);
		if (buf[0] == '\n' && buf[1] == '\0')
			return (s);
	}
}

void	exec_fils(char **line, t_env *env)
{
	int	status;
	int	redi_in;
	int	redi_out;

	redi_in = 0;
	redi_out = 1;
	if (line == NULL || line[0] == NULL)
		exit(2);
	if (ispipes(line, 1) > 0)
	{
		g_status_n_pid[1] = 1;
		pipes(line, env, -1);
	}
	else
	{
		status = redirections(line, &redi_out, &redi_in, env);
		g_status_n_pid[0] = status;
		if (status != 0)
			free_all(line, env, NULL);
		else if (ispipes(line, 2) != -1 && cmd(line[0], line, env) == -1)
			exec_instruction(line[0], line, env);
	}
	exit(g_status_n_pid[0]);
}

void	exec_fork(char **bigline, char **line, t_env *env)
{
	pid_t	pid;
	int		status;

	if (ispipes(line, 0) > 0 || is_cmd_env(line) == -1)
	{
		g_status_n_pid[1] = -10;
		pid = fork();
		if (pid < 0)
			error_sys("fork", errno);
		if (pid == 0)
		{
			free_dtab(bigline);
			g_status_n_pid[1] = 0;
			exec_fils(line, env);
		}
		else
		{
			g_status_n_pid[1] = (int)pid;
			waitpid(-1, &status, 0);
			if (WIFEXITED(status))
				g_status_n_pid[0] = WEXITSTATUS(status);
		}
	}
	else
		cmd_env(line, env, bigline);
}

void	boucle_instructions(char **bigline, t_env *env)
{
	int		i;
	char	*tmp;
	char	**line;

	i = -1;
	while (bigline[++i] != NULL)
	{
		bigline[i] = replace_var(bigline[i], env);
		line = ft_split(bigline[i], " ");
		normalize_dtab(line, 0);
		joker(&line);
		normalize_dtab(line, 1);
		exec_fork(bigline, line, env);
		if (line != NULL && line[0] != NULL)
		{
			tmp = ft_strmcat(ft_strdup("_="), line[0]);
			export(tmp, env);
			free(tmp);
		}
		if (line != NULL)
		{
			free_dtab(line);
			line = NULL;
		}
	}
}
