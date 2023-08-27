/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/27 12:23:16 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_m	*g_m;

// First process or last process of 2
int	first_process(t_m *m, int i, int n)
{
	if (!i)
	{
		if (n > 2)
			close_pipe(m->pipefd1);
		close(m->pipefd0[0]);
		if (dup2(m->pipefd0[1], STDOUT_FILENO) == -1)
			exit_error(m, "process1/dup2", 1);
		close(m->pipefd0[1]);
		return (1);
	}
	else if (n == 2)
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
int	last_process(t_m *m, int i, int n)
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
int	inter_process(t_m *m, int i, int n)
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

int	end_process(t_m *m, int i, int n)
{
	if (i && i % 2)
		close_pipe(m->pipefd0);
	else if (i && n > 2)
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
	if (n > 3 && i && i < n - 2)
	{
		if (i % 2)
			pipe(m->pipefd0);
		else if (n > 2)
			pipe(m->pipefd1);
	}
}

void	process(t_m *m, int i, int n)
{
	int		j;

	m->pid[i] = fork();
	if (m->pid[i] == -1)
		return_error(m, "fork", 1, 1);
	else if (!m->pid[i])
	{
		if (n > 1)
		{
			if (first_process(m, i, n))
				;
			else if (i == n - 1)
				last_process(m, i, n);
			else
				inter_process(m, i, n);
		}
		command(m, n);
	}
	else
		end_process(m, i, n);
}
