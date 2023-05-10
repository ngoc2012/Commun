/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/10 09:11:45 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

void	echo(t_m *m, char **args)
{
	char	*s;

	if (!args)
		write(1, "\n\n", 2);
	while (*args)
	{
		ft_putstr_fd(*args, 1);
		args++;
		if (*args)
			write(1, " ", 1);
	}
	if (!ft_strncmp(args[0], "-n", 3))
		write(1, "\n", 1);
	m->exit_code = 0;
}
