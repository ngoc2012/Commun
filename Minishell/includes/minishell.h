/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/03 09:51:27 by ngoc             ###   ########.fr       */
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
	char	**env;
	int	exit_code;
	char	cwd[PATH_MAX];
}	t_m;

void	echo(t_m *m, char *command);
char	*strjoinm(char *des, char *src, int len_des, int buffer);
void	pwd(t_m *m);
void	cd(t_m *m, char *path);
char	*get_env_name(char *name, char **environ);
char	*str_env(char *s, int len, t_m *m, char del);

#endif
