/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/19 19:51:54 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int	echo(t_m *m, char **args)
{
	int	i;

	if (!args)
		write(1, "\n\n", 2);
	i = 0;
	while (args[++i])
	{
		if (i > 1)
			write(1, " ", 1);
		ft_putstr_fd(args[i], 1);
	}
	if (ft_strncmp(args[1], "-n", 3))
		write(1, "\n", 1);
	m->exit_code = 0;
	return (1);
}
