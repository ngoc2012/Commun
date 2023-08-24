/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/08 13:52:23 by ngoc             ###   ########.fr       */
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
		if (ft_strncmp(m->args[i], "-n", 3))
		{
			if (n > 0)
				write(fd, " ", 1);
			if (ft_strncmp(m->args[i], "\\", 2))
				ft_putstr_fd(m->args[i], fd);
			n++;
		}
	}
}

int	echo0(t_m *m, int fd)
{
	int	i;
	int	i0;
	int	n;

	if (!*m->args)
	{
		write(fd, "\n\n", 2);
		return (1);
	}
	i = 0;
	i0 = 1;
	if (m->args[1] && !ft_strncmp(m->args[1], "-n", 3))
	{
		i++;
		i0++;
	}
	put_str(m, i, fd);
	if (ft_strncmp(m->args[1], "-n", 3))
		write(fd, "\n", 1);
	if (fd != 1)
		close(fd);
	m->exit_code = 0;
	return (1);
}
