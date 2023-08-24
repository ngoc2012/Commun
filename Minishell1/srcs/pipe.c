/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/18 00:40:51 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_process_level;

void	free_args(t_m *m)
{
	if (!m->args)
		return ;
	while (--m->argc > -1)
		if (m->args[m->argc])
			free(m->args[m->argc]);
	free(m->args);
}

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int	end_pipe(t_m *m)
{
	free_array_str(&m->coms, 1);
	if (m->fout > 1)
	{
		m->fout = 1;
		dup2(m->fout0, STDOUT_FILENO);
		close(m->fout0);
	}
	if (m->heredocf)
	{
		unlink(m->heredocf);
		free(m->heredocf);
		m->heredocf = 0;
	}
	if (m->fin)
	{
		m->fin = 0;
		dup2(m->fin0, STDIN_FILENO);
		close(m->fin0);
	}
	if (!m->args && m->exit_code == 2)
		return (0);
	return (1);
}

//printf("pipes  i = %d|%s|\n", i, m->coms[i]);
int	arg_pipe(t_m *m, char *path, int i, int n)
{
	m->args = split_args(m->coms[i], m);
	if (!m->args && m->exit_code == 2)
	{
		if (n > 1)
			close_pipe(m->pipefd0);
		if (n > 2)
			close_pipe(m->pipefd1);
		return (0);
	}
	if (m->args && *m->args && !builtins(m, i, n))
	{
		path = abs_path(m, m->args[0]);
		if (!ft_strncmp(m->args[0], "./minishell", 12)
			|| !ft_strncmp(path, m->ffn, ft_strlen(m->ffn) + 1))
		{
			g_process_level++;
			m->has_child = 1;
		}
		free(path);
		process(m, i, n);
	}
	free_args(m);
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
		return (syntaxe_error(m));
	n = -1;
	while (m->coms[++n])
		if (n && !ft_strlen(m->coms[n]))
			return (syntaxe_error(m));
	if (n > 1)
		pipe(m->pipefd0);
	if (n > 2)
		pipe(m->pipefd1);
	i = -1;
	while (++i < n)
		if (!arg_pipe(m, path, i, n))
			break ;
	return (end_pipe(m));
}
