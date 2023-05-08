/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/07 18:13:55 by ngoc             ###   ########.fr       */
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
# include "ft_printf.h"
# include "libft.h"

// minishell struct
typedef struct	s_m
{
	char	*s;
	char	**env;
	int	exit_code;
	char	cwd[PATH_MAX];
	char	syntax_error;
}	t_m;

void	echo(t_m *m, char **args);
char	*strjoinm(char *des, char *src, int len_des, int buffer);
void	pwd(t_m *m);
void	cd(t_m *m, char *path);
char	*get_env_name(char *name, char **environ);
char	*str_env(char *s, int len, t_m *m, char del);
char	*parse(char *s, t_m *m);
t_list	*split_ops(char *s, t_m *m);
void	print_content(void *s);
int	n_args(char *s);
char	**split_args(char *s);

#endif
