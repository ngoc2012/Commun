/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/16 07:41:52 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	exit_error(t_m *m, char *mess, int exit_code)
{
	if (mess)
		perror(mess);
	g_exit_code = exit_code;
	free_m(m, 1);
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
	g_exit_code = exit_code;
	free_m(m, 0);
	return (0);
}
