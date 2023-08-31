/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/31 09:16:15 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

static int	end_pipe(t_m *m)
{
	free_array_str(&m->coms, 1);
	free_files(m);
	if (m->heredocf)
	{
		unlink(m->heredocf);
		free(m->heredocf);
		m->heredocf = 0;
	}
	free_m_arg(m);
	if (!m->args && m->exit_code == 2)
		return (0);
	return (1);
}

static int	error_split_args(t_m *m, int n)
{
	if (m->exit_code == 2)
	{
		if (n > 1)
			close_pipe(m->pipefd0);
		if (n > 2)
			close_pipe(m->pipefd1);
	}
	free_m_arg(m);
	return (0);
}

int	arg_pipe(t_m *m, char *path, int i, int n)
{
	if (!split_args(m->coms[i], m))
		return (error_split_args(m, n));
	if (m->args && *m->args && !builtins(m, i, n))
	{
		path = abs_path(m, m->args[0]);
		if (!ft_strncmp(m->args[0], "./minishell", 12)
			|| !ft_strncmp(path, m->ffn, ft_strlen(m->ffn) + 1))
		{
			m->process_level++;
			m->has_child = 1;
		}
		free(path);
		process(m, i, n);
	}
	free_m_arg(m);
	m->n_wildcards = 0;
	return (1);
}

/*
Execute a command with or without pipe.
A command is a string between between || ; and &&.
*/
int	pipes(char *s, t_m *m)
{
	int		i;
	int		j;
	int		n;
	pid_t	pid;
	char	*path;

	path = 0;
	m->coms = ft_split_quote(s, '|');
	if (!m->coms)
		return (return_error(m, "syntaxe error", 2, 0));
	n = -1;
	while (m->coms[++n])
		if (n && !ft_strlen(m->coms[n]))
			return (return_error(m, "syntaxe error", 2, 0));
	if (n > 1)
		pipe(m->pipefd0);
	if (n > 2)
		pipe(m->pipefd1);
	i = -1;
	while (++i < n)
		if (!arg_pipe(m, path, i, n) && m->exit_code == 2)
			break ;
	return (end_pipe(m));
}
