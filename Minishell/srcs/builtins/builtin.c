/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/06/17 15:29:29 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	get_fd(t_m *m, int i, int n)
{
	if (n == 2 && !i)
	{
		printf("fd = pipefd0\n");
		return (m->pipefd0[1]);
	}
	else if (n > 2)
	{
		if (i % 2)
		{
			printf("fd = pipefd1\n");
			return (m->pipefd1[1]);
		}
		else 
		{
			printf("fd = pipefd0\n");
			return (m->pipefd0[1]);
		}
	}
	else
		return (1);
}

/*
Execute a built-in command elementary
*/
int	builtins(t_m *m, int i, int n)
{
	int	fd;

	if (!ft_strncmp(m->args[0], "echo", 5))
	{
		fd = get_fd(m, i, n);
		return (echo(m, m->args, fd));
	}
	else if (!ft_strncmp(m->args[0], "export", 7))
	{
		fd = get_fd(m, i, n);
		if (n > 1)
			return (1);
		else
			return (expt(m, m->args));
	}
	else if (!ft_strncmp(m->args[0], "pwd", 4))
	{
		fd = get_fd(m, i, n);
		ft_putstr_fd(m->cwd, fd);
		write(1, "\n", 1);
		m->exit_code = 0;
		return (1);
	}
	else if (!ft_strncmp(m->args[0], "cd", 3))
	{
		fd = get_fd(m, i, n);
		if (n > 1)
			return (1);
		else
			return (cd(m, m->args[1]));
	}
	else if (!ft_strncmp(m->args[0], "exit", 5))
	{
		if (n > 1)
			return (1);
		free_ss(m->args);
		free_ss(m->coms);
		if (m->infix)
			ft_lstclear(&m->infix, free);
		if (m->envs)
			ft_lstclear(&m->envs, free);
		add_history(m->s);
		rl_free(m->s);
		if (n > 1)
		{
			close(m->pipefd0[0]);
			close(m->pipefd0[1]);
		}
		if (n > 2)
		{
			close(m->pipefd1[0]);
			close(m->pipefd1[1]);
		}
		exit(m->exit_code);
	}
	return (0);
}
