/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/19 19:55:02 by ngoc             ###   ########.fr       */
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

// define HOME "/mnt/nfs/homes/"
# define HOME "/home/"

typedef struct	s_m
{
	char	*s;
	char	**env;
	char	**coms;
	char	**args;
	int		exit_code;
	int		*pipefd;
	char	cwd[PATH_MAX];
	char	syntax_error;
	char	*right;
	char	*left;
	char	*right2;
	char	*left2;
	t_list	*infix;
	t_list	*envs;
}	t_m;

int	echo(t_m *m, char **args);
int	expt(t_m *m, char **args);
char	*strjoinm(char *des, char *src, int len_des, int buffer);
void	pwd(t_m *m);
int	cd(t_m *m, char *path);
char	*get_env_name(char *name, char **environ);
char	*str_env(char *s, int len, t_m *m);
int	split_ops(char *s, t_m *m);
void	print_content(void *s);
char	**split_args(char *s, t_m *m);
void	free_ss(char **ss);
void	free_none(void *);
void	exec(t_m *m, char **args);
char	*ft_strndup(char *s, int len);
void	wildcards(char *s, t_list **args, t_m *m);
int	pipes(char *s, t_m *m);
void	free_m(t_m *m);
int	isenv(char c);

#endif
