/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/06/10 10:07:00 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int	echo(t_m *m, char **args, int fd)
{
	int	i;
	int	i0;

	if (!*args)
	{
		write(fd, "\n\n", 2);
		return (1);
	}
	i = 0;
	i0 = 1;
	if (args[1] && !ft_strncmp(args[1], "-n", 3))
	{
		i++;
		i0++;
	}
	while (args[++i])
	{
		if (i > i0)
			write(fd, " ", 1);
		ft_putstr_fd(args[i], fd);
	}
	if (ft_strncmp(args[1], "-n", 3))
		write(fd, "\n", 1);
	if (fd != 1)
		close(fd);
	m->exit_code = 0;
	return (1);
}
