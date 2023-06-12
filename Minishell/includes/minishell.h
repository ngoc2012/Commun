/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/06/11 20:11:24 by ngoc             ###   ########.fr       */
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

# define BUFFER_SIZE 100

typedef struct	s_m
{
	char	*s;
	char	**env;
	char	**coms;
	char	**args;
	int		exit_code;
	int		*pipefd;
	char	*cwd;
	char	syntax_error;
	t_list	*infix;
	t_list	*envs;
	char	*heredoc;
	char	*heredocf;
	int	fin;
	int	fin0;
	int	fout;
	int	fout0;
}	t_m;

int	echo(t_m *m, char **args, int fd);
int	expt(t_m *m, char **args);
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

#endif
