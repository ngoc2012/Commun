/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/06/04 01:19:50 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Execute a built-in command elementary
*/
int	builtins(t_m *m, int i, int n)
{
	if (!ft_strncmp(m->args[0], "echo", 5))
	{
		if (n > 1 && i < n - 1)
		{
			if (i > 0)
				close(m->pipefd[2 * (i - 1)]);
			return (echo(m, m->args, m->pipefd[2 * i + 1]));
		}
		if (n > 1)
			close(m->pipefd[2 * (i - 1)]);
		return (echo(m, m->args, m->fout));
	}
	else if (!ft_strncmp(m->args[0], "export", 7))
	{
		if (n > 1)
			return (1);
		else
			return (expt(m, m->args));
	}
	else if (!ft_strncmp(m->args[0], "pwd", 4))
	{
		if (getcwd(m->cwd, sizeof(m->cwd)))
		{
			if (n > 1 && i < n - 1)
			{
				if (i > 0)
					close(m->pipefd[2 * (i - 1)]);
				ft_putstr_fd(m->cwd, m->pipefd[2 * i + 1]);
				write(m->pipefd[2 * i + 1], "\n", 1);
				close(m->pipefd[2 * i + 1]);
				return (1);
			}
			if (n > 1)
				close(m->pipefd[2 * (i - 1)]);
			ft_putstr_fd(m->cwd, 1);
			write(1, "\n", 1);
			m->exit_code = 0;
			return (1);
		}
		perror("getcwd() error");
		m->exit_code = 1;
		return (1);
	}
	else if (!ft_strncmp(m->args[0], "cd", 3))
	{
		if (n > 1)
			return (1);
		else
			return (cd(m, m->args[1]));
	}
	else if (!ft_strncmp(m->args[0], "exit", 5))
	{
		if (n > 1)
			return (1);
		if (m->fout != 1)
			close(m->fout);
		free_ss(m->args);
		free_ss(m->coms);
		if (m->pipefd)
			free(m->pipefd);
		ft_lstclear(&m->infix, free);
		ft_lstclear(&m->envs, free);
		add_history(m->s);
		rl_free(m->s);
		exit(m->exit_code);
	}
	return (0);
}
