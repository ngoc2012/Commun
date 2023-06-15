/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/06/14 16:30:28 by ngoc             ###   ########.fr       */
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
	i = -1;
	while (m->coms[++i])
	{
		//printf("i = %d\n", i);
		m->args = split_args(m->coms[i], m);
		if (!m->args || !(*m->args))
		{
			free_ss(m->args);
			break ;
		}
		pipe(m->pipefd);
		if (!builtins(m, i, n))
			process(m, i, n);
		free_ss(m->args);
	}
	close(m->pipefd[0]);
	close(m->pipefd[1]);
	free_ss(m->coms);
	//printf("fout = %d\n", m->fout);
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

