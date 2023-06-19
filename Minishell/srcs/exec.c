/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/06/19 16:08:19 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	//printf("s = %s\n", s);
	m->coms = ft_split(s, '|');
	n = -1;
	while (m->coms[++n])
		;
	if (n > 1)
	{
		printf("First pipefd0\n");
		pipe(m->pipefd0);
	}
	if (n > 2)
	{
		printf("First pipefd1\n");
		pipe(m->pipefd1);
	}
	i = -1;
	while (++i < n)
	{
		//printf("i = %d\n", i);
		m->args = split_args(m->coms[i], m);
		if (!m->args || !(*m->args))
		{
			free_ss(m->args);
			break ;
		}
		if (!builtins(m, i, n))
			process(m, i, n);
		free_ss(m->args);
	}
	free_ss(m->coms);
	if (m->fout != 1 && m->fout)
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
	return (1);
}

