/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/14 09:39:16 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_forks;

// First process or last process of 2
int	first_process(t_m *m, int i)
{
	if (!i)
	{
		if (m->n_pipes > 2)
			close_pipe(m->pipefd1);
		close(m->pipefd0[0]);
		if (dup2(m->pipefd0[1], STDOUT_FILENO) == -1)
			exit_error(m, "dup2", 1);
		close(m->pipefd0[1]);
		return (1);
	}
	else if (m->n_pipes == 2)
	{
		close(m->pipefd0[1]);
		if (dup2(m->pipefd0[0], STDIN_FILENO) == -1)
			exit_error(m, "dup2", 1);
		close(m->pipefd0[0]);
		return (1);
	}
	return (0);
}

// Last process
void	last_process(t_m *m, int i)
{
	if (i % 2)
	{
		close_pipe(m->pipefd1);
		close(m->pipefd0[1]);
		if (dup2(m->pipefd0[0], STDIN_FILENO) == -1)
			exit_error(m, "dup2", 1);
		close(m->pipefd0[0]);
	}
	else
	{
		close_pipe(m->pipefd0);
		close(m->pipefd1[1]);
		if (dup2(m->pipefd1[0], STDIN_FILENO) == -1)
			exit_error(m, "dup2", 1);
		close(m->pipefd1[0]);
	}
}

// Intermediate process
void	inter_process(t_m *m, int i)
{
	if (i % 2)
	{
		close(m->pipefd0[1]);
		if (dup2(m->pipefd0[0], STDIN_FILENO) == -1)
			exit_error(m, "dup2", 1);
		close(m->pipefd0[0]);
		close(m->pipefd1[0]);
		if (dup2(m->pipefd1[1], STDOUT_FILENO) == -1)
			exit_error(m, "dup2", 1);
		close(m->pipefd1[1]);
	}
	else
	{
		close(m->pipefd1[1]);
		if (dup2(m->pipefd1[0], STDIN_FILENO) == -1)
			exit_error(m, "dup2", 1);
		close(m->pipefd1[0]);
		close(m->pipefd0[0]);
		if (dup2(m->pipefd0[1], STDOUT_FILENO) == -1)
			exit_error(m, "dup2", 1);
		close(m->pipefd0[1]);
	}
}

void	end_process(t_m *m, int i)
{
	if (m->n_pipes > 1 && i && i % 2)
		close_pipe(m->pipefd0);
	else if (i && m->n_pipes > 2)
		close_pipe(m->pipefd1);
	if (m->n_pipes > 3 && i && i < m->n_pipes - 2)
	{
		if (i % 2)
			pipe(m->pipefd0);
		else if (m->n_pipes > 2)
			pipe(m->pipefd1);
	}
}

int	process(t_m *m, int i)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return_error(m, "fork", 1, 1);
	else if (!pid)
	{
		if (m->n_pipes > 1)
		{
			if (first_process(m, i))
				;
			else if (i == m->n_pipes - 1)
				last_process(m, i);
			else
				inter_process(m, i);
		}
		command(m);
	}
	else
	{
		g_forks++;
		end_process(m, i);
	}
	return (pid);
}
