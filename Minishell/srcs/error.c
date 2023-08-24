/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/23 23:12:28 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(t_m *m, char *mess, int exit_code)
{
	if (mess)
		perror(mess);
	m->exit_code = exit_code;
	free_m(m);
	exit(exit_code);
}

int	return_error(t_m *m, char *mess, int exit_code, int is_perror)
{
	if (is_perror)
		perror(mess);
	else
	{
		ft_putstr_fd(mess, 2);
		ft_putstr_fd("\n", 2);
	}
	m->exit_code = exit_code;
	free_m(m);
	return (0);
}
