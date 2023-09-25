/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/25 15:45:09 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	redir_error(char *mess, int exit_code, int is_perror)
{
	if (is_perror)
		perror(mess);
	else
	{
		ft_putstr_fd(mess, 2);
		ft_putstr_fd("\n", 2);
	}
	g_exit_code = exit_code;
	return (0);
}

int	redir_in(t_m *m, char *s)
{
	if (!s)
		return (0);
	if (m->fin && m->fin != -1)
	{
		close(m->fin);
		m->fin = 0;
		if (dup2(m->fin0, STDIN_FILENO) == -1)
			return (redir_error("dup2", 1, 1));
		close(m->fin0);
	}
	m->fin = open(s, O_RDONLY);
	if (m->fin == -1)
		ft_putstr_fd(s, 2);
	if (s)
		free(s);
	if (m->fin == -1)
		return (redir_error(" ", 1, 1));
	m->fin0 = dup(STDIN_FILENO);
	if (m->fin0 == -1)
		return (redir_error("dup", 1, 1));
	if (dup2(m->fin, STDIN_FILENO) == -1)
		return (redir_error("dup2", 1, 0));
	return (1);
}
