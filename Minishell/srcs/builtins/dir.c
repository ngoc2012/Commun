/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:01:37 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/02 10:06:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_m *m)
{
	if (getcwd(m->cwd, sizeof(m->cwd)))
	{
		ft_putstr_fd(m->cwd, 1);
		m->exit_code = 0;
	}
	else
	{
		perror("getcwd() error");
		m->exit_code = 1;
	}
	write(1, "\n", 1);
}

void	cd(t_m *m, char *path)
{
	char	*s;

	if (chdir(path))
	{
		s = 0;
		s = strjoinm(s, "minishell: cd: ", 0, 15);
		s = strjoinm(s, path, ft_strlen(s), ft_strlen(path));
		perror(s);
		if (s)
			free(s);
		m->exit_code = 1;
	}
	else
		m->exit_code = 0;
}
