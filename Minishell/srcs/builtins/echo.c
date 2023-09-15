/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/14 09:15:29 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static void	put_str(t_m *m, int i, int fd)
{
	int	n;

	n = 0;
	while (++i < m->argc)
	{
		if (n > 0)
			write(fd, " ", 1);
		ft_putstr_fd(m->args[i], fd);
		n++;
	}
}

int	new_line(t_m *m, int i)
{
	int	j;

	if (m->args[i] && !ft_strncmp(m->args[i], "-n", 2))
	{
		j = 2;
		while (m->args[i][j] && m->args[i][j] == 'n')
			j++;
		if (m->args[i][j])
			return (1);
		return (0);
	}
	return (1);
}

int	echo0(t_m *m, int fd)
{
	int	i;
	int	n_l;

	if (!*m->args)
	{
		write(fd, "\n\n", 2);
		return (1);
	}
	i = 0;
	n_l = new_line(m, i + 1);
	while (m->args[i] && !new_line(m, i + 1))
		i++;
	put_str(m, i, fd);
	if (n_l)
		write(fd, "\n", 1);
	if (fd != 1)
		close(fd);
	m->exit_code = 0;
	return (1);
}
