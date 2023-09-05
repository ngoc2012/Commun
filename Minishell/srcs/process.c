/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/05 11:31:38 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_m	*g_m;

// First process or last process of 2
int	first_process(t_m *m, int i)
{
	if (!i)
	{
		if (m->n_pipes > 2)
			close_pipe(m->pipefd1);
		close(m->pipefd0[0]);
		if (dup2(m->pipefd0[1], STDOUT_FILENO) == -1)
			exit_error(m, "process1/dup2", 1);
		close(m->pipefd0[1]);
		return (1);
	}
	else if (m->n_pipes == 2)
	{
		close(m->pipefd0[1]);
		if (dup2(m->pipefd0[0], STDIN_FILENO) == -1)
			exit_error(m, "process2/dup2", 1);
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
			exit_error(m, "process3/dup2", 1);
		close(m->pipefd0[0]);
	}
	else
	{
		close_pipe(m->pipefd0);
		close(m->pipefd1[1]);
		if (dup2(m->pipefd1[0], STDIN_FILENO) == -1)
			exit_error(m, "process4/dup2", 1);
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
			exit_error(m, "process5/dup2", 1);
		close(m->pipefd0[0]);
		close(m->pipefd1[0]);
		if (dup2(m->pipefd1[1], STDOUT_FILENO) == -1)
			exit_error(m, "process6/dup2", 1);
		close(m->pipefd1[1]);
	}
	else
	{
		close(m->pipefd1[1]);
		if (dup2(m->pipefd1[0], STDIN_FILENO) == -1)
			exit_error(m, "process7/dup2", 1);
		close(m->pipefd1[0]);
		close(m->pipefd0[0]);
		if (dup2(m->pipefd0[1], STDOUT_FILENO) == -1)
			exit_error(m, "process8/dup2", 1);
		close(m->pipefd0[1]);
	}
}

void	end_process(t_m *m, int i)
{
	if (i && i % 2)
		close_pipe(m->pipefd0);
	else if (i && m->n_pipes > 2)
		close_pipe(m->pipefd1);
	waitpid(m->pid[i], &m->exit_code, 0);
	if (m->has_child)
	{
		m->process_level = 0;
		m->has_child = 0;
	}
	if (WIFEXITED(m->exit_code))
		m->exit_code = WEXITSTATUS(m->exit_code);
	else if (WIFSIGNALED(m->exit_code))
		m->exit_code = WTERMSIG(m->exit_code) + 128;
	if (m->n_pipes > 3 && i && i < m->n_pipes - 2)
	{
		if (i % 2)
			pipe(m->pipefd0);
		else if (m->n_pipes > 2)
			pipe(m->pipefd1);
	}
}

void	process(t_m *m, int i)
{
	int		j;

	m->pid[i] = fork();
	if (m->pid[i] == -1)
		return_error(m, "fork", 1, 1);
	else if (!m->pid[i])
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
		end_process(m, i);
}
