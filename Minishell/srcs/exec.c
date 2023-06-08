/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/06/08 12:00:09 by ngoc             ###   ########.fr       */
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

	m->coms = ft_split(s, '|');
	n = -1;
	while (m->coms[++n])
		;
	//printf("n = %d\n", n);
	m->pipefd = 0;
	if (n > 1)
	{
		m->pipefd = malloc((n - 1) * 2 * sizeof(int));
		i = -1;
		while (++i < n - 1)
			if (pipe(&m->pipefd[2 * i]) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
	}
	i = -1;
	while (m->coms[++i])
	{
		//printf("i = %d\n", i);
		m->args = split_args(m->coms[i], m);
		if (!m->args)
			break ;
		if (!builtins(m, i, n))
			process(m, i, n);
		free_ss(m->args);
	}
	if (m->pipefd)
		free(m->pipefd);
	free_ss(m->coms);
	if (m->fout != 1)
	{
		m->fout = 1;
		dup2(m->fout0, STDOUT_FILENO);
		close(m->fout0);
	}
	if (m->fin)
	{
		m->fin = 0;
		dup2(m->fin0, STDIN_FILENO);
		close(m->fin0);
	}
	return (1);
}

