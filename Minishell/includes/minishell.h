/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/16 15:03:32 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>

# define BUFFER_SIZE 100

typedef struct s_c
{
	int		i;
	int		i0;
	int		len;
	int		n_c;
	int		n_o;
	int		err;
	char	*s;
	char	*o;
	char	d;
	char	in_double_quotes;
	char	first_arg;
	t_list	*args;
}	t_c;

typedef struct s_m
{
	char	*s;
	char	**env;
	char	*com;
	char	**coms;
	char	**args;
	char	**ss;
	t_list	*infix;
	t_list	*args_list;
	int		forks;
	int		pipefd0[2];
	int		pipefd1[2];
	char	cwd[PATH_MAX];
	char	heredocf[PATH_MAX];
	int		argc;
	int		fin;
	int		fin0;
	int		fout;
	int		fout0;
	int		n_pipes;
}	t_m;

int		echo0(t_m *m, int fd);
int		expt(t_m *m);
int		expt_all(t_m *m, int fd);
int		cd(t_m *m, char *path);
int		split_ops(char *s, t_m *m);
int		pipes(char *s, t_m *m);
int		isenv(char c);
int		builtins(t_m *m, int i);
int		ft_strdcmp(const char *s1, const char *s2);
int		chr_pos(char *s, char c);
int		priorities_operators(char *s, t_m *m);
int		infix_priorities_operators(t_list *p, t_m *m);
int		is_all_env(char *s, int p);
int		builtin_exit(t_m *m);
int		redir_out(t_m *m, char *s, int append);
int		redir_in(t_m *m, char *s);
int		heredoc(t_m *m);
int		ft_strcmp_val(char *s1, char *s2);
int		wild_files_list(t_m *m, char *s, char **ss, t_list **args);
int		return_error(t_m *m, char *mess, int exit_code, int is_perror);
int		redir_error(char *mess, int exit_code, int is_perror);
int		split_args(char *s, t_m *m);
int		get_str_env(char *s, t_m *m, t_c *c);
int		get_fd(t_m *m, int i);
int		free_heredoc(t_m *m);
int		check_heredoc(t_m *m, t_list *cur, t_list **here);
int		convert_heredoc(t_m *m);
int		process(t_m *m, int i);
int		get_str_env3(char *s, t_m *m, t_c *c);
void	command(t_m *m);
char	*strjoinm(char *des, char *src, int len_des, int buffer);
void	pwd(t_m *m);
char	*get_env_name(char *name, char **environ);
char	*str_env(char *s, int len, t_m *m, int first_arg);
char	*str_env2(char *s, int len, t_m *m);
void	print_content(void *s);
void	free_ss(char **ss);
void	free_none(void *s);
void	exec(t_m *m, char **args);
char	*ft_strndup(char *s, int len);
void	wildcards(char *s, t_list **args, t_m *m);
void	free_m(t_m *m, int free_env);
void	free_m_arg(t_m *m);
void	redir(t_list *args, t_m *m);
char	*get_home(t_m *m);
char	*remove_quotes(char *s, int len, t_m *m);
void	init(t_m *m);
char	**ft_split_quote(char *str, char charset);
char	*abs_path(t_m *m, char *path);
char	*get_env(char *s, char **ss);
void	close_pipe(int *fd);
t_list	*get_args_list(char *s);
void	exit_error(t_m *m, char *mess, int exit_code);
void	free_files(t_m *m);
void	signal_heredoc(void);
void	set_pipe(t_m *m, int i);
void	convert_exit_code(void);
void	fn_heredoc(t_m *m);
t_list	*get_args_list_wild(char *s, t_m *m);
char	*remove_dollar(char *s);
char	*relative_path0(t_m *m, char *path);
void	main_signal_handler(int sig);

#endif
