/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init(struct termios *new_term, struct termios *old_term, char **envp,
char *name)
{
	t_env	*env;

	g_status_n_pid[0] = 0;
	g_status_n_pid[2] = 1;
	env = fill_env(envp, name);
	signal(SIGINT, signal_minishell);
	signal(SIGQUIT, signal_minishell);
	if (tgetent(NULL, get_env("TERM", env)) < 1)
		error_sys("tgetent", -1);
	get_term_attr(new_term, old_term);
	return (env);
}

void	prompt(void)
{
	char	b[255];

	if (g_status_n_pid[2] != 1)
	{
		ft_putstr_fd("\033[1;32m", 2);
		write(2, "======> ", 8);
		ft_putstr_fd("\033[0m", 2);
		return ;
	}
	tputs(tgetstr("vi", NULL), 1, ft_putchar_tty);
	ft_putstr_fd("\033[1;32m", 2);
	write(2, "===", 3);
	ft_putstr_fd("\033[1;34m", 2);
	write(2, getcwd(b, 255), ft_strlen(getcwd(b, 255)));
	ft_putstr_fd("\033[1;32m", 2);
	write(2, "===> ", 5);
	ft_putstr_fd("\033[0m", 2);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_tty);
	return ;
}

void	non_interactive(char *s, t_env *env)
{
	char	**line;

	line = interpret_line(s);
	if (line != NULL)
		boucle_instructions(line, env);
	exit(g_status_n_pid[0]);
}

void	interpret_n_treat(char *s, t_env *env)
{
	char			**line;

	fill_history(s, env);
	line = interpret_line(s);
	if (line != NULL)
	{
		boucle_instructions(line, env);
		free_dtab(line);
	}
	return ;
}

int	main(int ac, char **av, char **envp)
{
	char			*s;
	t_env			*env;
	struct termios	new_term;
	struct termios	old_term;
	t_coor			cursor_0;

	env = init(&new_term, &old_term, envp, av[0]);
	if (ac > 2 && ft_strcmp(av[1], "-c") == 0)
		non_interactive(ft_strdup(av[2]), env);
	if (isatty(0) != 1)
	{
		ft_putstr_fd("minishell: Entrée standard: Mauvais descripteur de ", 2);
		ft_putstr_fd("fichier\n", 2);
		exit(2);
	}
	while (1)
	{
		g_status_n_pid[1] = -10;
		prompt();
		tcsetattr(0, TCSANOW, &new_term);
		cursor_0 = get_cursor_pos();
		s = read_instruction_line(env, &cursor_0);
		tcsetattr(0, TCSANOW, &old_term);
		interpret_n_treat(s, env);
	}
}
