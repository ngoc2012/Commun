/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/15 22:55:19 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "ft_printf.h"
# include "libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>

# define BUFFER_SIZE 100

typedef struct	s_p
{
	int	level;
	int	last_level;
	int	blocked;
}	t_p;

typedef struct	s_c
{
	char	*s;
	char	*o;
	int	i;
	int	i0;
	int	len;
	int	n_c;
	int	n_o;
	char	in_double_quotes;
}	t_c;

typedef struct	s_m
{
	char	*s;
	char	**env;
	char	**coms;
	char	**args;
	int		exit_code;
	int		pipefd0[2];
	int		pipefd1[2];
	pid_t	pid[10000];
	char	cwd[PATH_MAX];
	char	syntax_error;
	char	has_child;
	t_list	*infix;
	char	*heredoc;
	char	*heredocf;
	char	*ffn;
	int		argc;
	int		fin;
	int		fin0;
	int		fout;
	int		fout0;
	int		n_wildcards;
}	t_m;

int	echo0(t_m *m, int fd);
int	expt(t_m *m);
int	expt_all(t_m *m, int fd);
char	*strjoinm(char *des, char *src, int len_des, int buffer);
void	pwd(t_m *m);
int	cd(t_m *m, char *path);
char	*get_env_name(char *name, char **environ);
char	*str_env(char *s, int len, t_m *m);
int	split_ops(char *s, t_m *m);
void	print_content(void *s);
void	free_ss(char **ss);
void	free_none(void *);
void	exec(t_m *m, char **args);
char	*ft_strndup(char *s, int len);
void	wildcards(char *s, t_list **args, t_m *m);
int	pipes(char *s, t_m *m);
void	free_m(t_m *m);
int	isenv(char c);
int	builtins(t_m *m, int i, int n);
void	process(t_m *m, int i, int n);
int	ft_strdcmp(const char *s1, const char *s2);
int	chr_pos(char *s, char c);
char	**split_args(char *s, t_m *m);
void	redir(t_list *args, t_m *m);
char	*get_home();
char	*remove_quotes(char *s, int len, t_m *m);
int	priorities_operators(char *s, t_m *m);
int	infix_priorities_operators(t_list *p, t_m *m);
void	init(t_m *m);
char	**ft_split_quote(char *str, char charset);
char	*abs_path(t_m *m, char *path);
char	*get_env(char *s, char **ss);
int	is_all_env(char *s, int p);
void	close_pipe(int *fd);
int	builtin_exit(t_m *m, int i, int n);
int	syntaxe_error(t_m *m);
char	*remove_quotes(char *s, int len, t_m *m);
int	redir_out(t_m *m, t_list **args, t_list **args0, char **ss0);
int	redir_in(t_m *m, t_list **args, t_list **args0, char **ss0);
int	heredoc(t_m *m, t_list **args, t_list **args0, char **ss0);
int	redir_error(t_m *m, t_list **args0, char **ss0, int exit_code);

#endif
