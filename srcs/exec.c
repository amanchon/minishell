/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**path_instruction(char *cmd, char **full_path, t_env *env)
{
	char	**path;

	if (get_env("PATH", env) == NULL
		|| ft_strcmp("", get_env("PATH", env)) == 0)
	{
		*full_path = relative_to_absolute(cmd);
		return (NULL);
	}
	*full_path = ft_strdup(get_env("PATH", env));
	path = ft_split(*full_path, ":");
	free(*full_path);
	if (path[0] == NULL)
	{
		free(path);
		*full_path = relative_to_absolute(cmd);
		return (NULL);
	}
	*full_path = ft_strmcatn(3, ft_strdup(path[0]), ft_strdup("/"),
			ft_strdup(cmd));
	return (path);
}

void	exec_instruction2(char *cmd, char **line, t_env *env, char **dtab_env)
{
	int		i;
	char	*full_path;
	char	**path_inst;

	i = 0;
	path_inst = path_instruction(cmd, &full_path, env);
	while (execve(full_path, line, dtab_env) == -1)
	{
		free(full_path);
		if (path_inst == NULL || path_inst[++i] == NULL)
		{
			error_exec(cmd, (int)errno);
			if (path_inst != NULL)
				free_dtab(path_inst);
			free_dtab(dtab_env);
			free_env(env);
			free_dtab(line);
			return ;
		}
		full_path = ft_strmcatn(3, ft_strdup(path_inst[i]), ft_strdup("/"),
				ft_strdup(cmd));
	}
}

void	exec_instruction(char *cmd, char **line, t_env *env)
{
	char	*full_path;
	char	**dtab_env;

	if (cmd == NULL || cmd[0] == '\0')
		return ;
	dtab_env = list_to_dtab_env(env);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/') || (cmd[0] == '.'
			&& cmd[1] == '.' && cmd[2] == '/'))
	{
		if (cmd[0] == '/')
			full_path = ft_strdup(cmd);
		else
			full_path = relative_to_absolute(cmd);
		if (execve(full_path, line, dtab_env) == -1)
			error_exec(cmd, (int)errno);
		free(full_path);
		free_dtab(dtab_env);
		free_env(env);
		free_dtab(line);
		return ;
	}
	exec_instruction2(cmd, line, env, dtab_env);
	return ;
}
