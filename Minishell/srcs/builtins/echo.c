/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/12 00:35:36 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

void	echo(t_m *m, char **args)
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
	free_m(m);
	exit(EXIT_SUCCESS);
}
