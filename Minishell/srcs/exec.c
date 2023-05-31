/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/30 18:33:14 by ngoc             ###   ########.fr       */
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
		if (!builtins(m, i, n))
			process(m, i, n);
		free_ss(m->args);
	}
	if (m->pipefd)
		free(m->pipefd);
	free_ss(m->coms);
	return (1);
}

