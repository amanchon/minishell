/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:14:43 by amanchon          #+#    #+#             */
/*   Updated: 2021/06/26 17:20:50 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <signal.h>
# include <dirent.h>

	int		g_status_n_pid[3];

typedef struct		s_coor
{
	int				x;
	int				y;
}					t_coor;

typedef struct		s_env
{
	char			*clef;
	char			*valeur;
	struct s_env	*next;
}					t_env;

char	*find_files(char **s_joker, char *dir_path, int i);
char	*insert(char *key, char *s, t_coor *cursor_0, t_coor cursor);
char	*insert_del(char *s, t_coor *cursor_0, t_coor cursor, int rpos);
char	*key127(char *s, t_coor *cursor_0, t_coor cursor, int rpos);
void	move_cursor_right(void);
void	move_cursor_left(void);
void	d_redi_nline(char **line, char **txt, t_env *env, t_coor *cursor_0);
int		dup2_n_close(int fd1, int fd2);
void	redi_suppr_line(char **line);
int		get_fd_redi_out(char **line, int i, int *fd_redi_out);
int		check_dim(t_coor dim_0, char **txt);
void	interpret_line_3(char **s, int *i, int quote, int dquote);
int		error_quote(int quote, int dquote, char *s);
int		ft_isdigit_string(char *s);
int		check_clef_env(char *s);
int		error_fd(char *line, int permission);
void	error_sys(char *line, int errnum);
int		is_error_pipe(char **dtab);
int		is_cmd_env(char **line);
void	normalize_dtab(char **s, int j);
void	suppr_line_dtab(char **s, int n);
int		check_input(char *s);
void	error_exit(char **line, t_env *env);
void	error_exec(char *cmd, int errnum);
void	error_cmd(char *cmd, char *symbol, char *msg, int status);
void	error_syntax(char *symbol);
void	ft_exit(char **line, t_env *env);
int		ft_putchar_tty(int c);
int		error_d_redirect(char *end);
void	prompt();
void	free_env(t_env *env);
t_coor	get_term_dimension(void);
t_coor	get_cursor_pos(void);
int		ft_echo(char **args);
char	*get_env(char *s, t_env *env);
void	see_env(t_env *env, int expor);
int		unset(char *s, t_env *env);
int		export(char *s, t_env *env);
void	cd(char **path, t_env *env);
char	**list_to_dtab_env(t_env *env);
t_env	*fill_env(char **env, char *name);
char	**split_var_env(char *s, t_env *env);
char	**interpret_line(char *s);
char	*suppr_chr(char *s, int i);
void	free_triple_tab(char ***t_tab);
void	exec_instruction(char *cmd, char **line, t_env *env);
int		cmd(char *cmd, char **line, t_env *env);
int		ispipes(char **line, int n);
char	***t_tab_pipes(char **line);
void	pipes(char **cmd, t_env *env, int i);
int		redirections(char **line, int *fd_out, int *fd_in, t_env *env);
int		fill_history(char *s, t_env *env);
char	*change_input(char *key, char *s, t_coor *cursor_0, t_env *env);
char	*find_cmd_history(char *s, int dir, int *line_hst, t_env *env);
void	signal_minishell(int signum);
void	exec_instruction(char *cmd, char **line, t_env *env);
int		cmd(char *cmd, char **line, t_env *env);
int		cmd_env(char **line, t_env *env);
void	get_term_attr(struct termios *new_term, struct termios *old_term);
char	*read_instruction_line(t_env *env, t_coor *cursor_0);
void	exec_fils(char **line, t_env *env);
void	boucle_instructions(char **line, t_env *env);
void	mark_var(char **s,int *i, int quote, int dquote);
void	mark_tilde(char **s,int *i, int quote, int dquote);
char	*replace_var(char *line, t_env *env);
char	*replace_var_spe_redi(char *line, t_env *env);
void	joker(char **line);
char	*relative_to_absolute(char *r_path);
t_coor	get_cursor_0(int rpos_cursor, t_coor cursor, t_coor dim);

#endif
