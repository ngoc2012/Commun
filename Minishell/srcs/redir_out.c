/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/16 07:30:51 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_out(t_m *m, char *s, int append)
{
	if (!s)
		return (0);
	if (m->fout != 1)
	{
		close(m->fout);
		m->fout = 1;
		if (dup2(m->fout0, STDOUT_FILENO) == -1)
			return (redir_error("dup2", 1, 1));
		close(m->fout0);
	}
	if (append)
		m->fout = open(s, O_CREAT | O_WRONLY | O_APPEND, 0664);
	else
		m->fout = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (m->fout == -1)
		ft_putstr_fd(s, 2);
	free(s);
	if (m->fout == -1)
		return (redir_error(" ", 1, 1));
	m->fout0 = dup(STDOUT_FILENO);
	if (m->fout0 == -1)
		return (redir_error("dup", 1, 1));
	if (dup2(m->fout, STDOUT_FILENO) == -1)
		return (redir_error("dup2", 1, 1));
	return (1);
}
