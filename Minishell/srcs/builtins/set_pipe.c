/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/14 09:38:28 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  
  Pipe[0]  Pipe[1]  Pipe[0]  Pipe[1]  Pipe[0]  Pipe[ ]
  Out  In  Out  In  Out  In  Out  In  Out  In  Out  In
  /     \ /      \ /      \ /      \ /      \ /      \
Pr[0]  Pr[1]    Pr[2]      ....	  Pr[i]     ....    Pr[n-1]

*/
void	set_pipe(t_m *m, int i)
{
	if (m->n_pipes > 1 && i)
	{
		if (i % 2)
			close_pipe(m->pipefd0);
		else if (m->n_pipes > 2)
			close_pipe(m->pipefd1);
	}
	if (m->n_pipes > 3 && i && i < m->n_pipes - 2)
	{
		if (i % 2)
			pipe(m->pipefd0);
		else if (m->n_pipes > 2)
			pipe(m->pipefd1);
	}
}

int	get_fd(t_m *m, int i)
{
	int	fd;

	fd = 1;
	if (m->n_pipes < 2)
		return (fd);
	if (i < m->n_pipes - 1)
	{
		if (i % 2)
			fd = m->pipefd1[1];
		else
			fd = m->pipefd0[1];
	}
	return (fd);
}
