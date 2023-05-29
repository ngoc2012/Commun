/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/28 14:33:45 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define BUFFER 100
int	check_builtins(t_m *m, int i, int n)
{
	if (!ft_strncmp(m->args[0], "export", 7))
		return (1);
	else if (!ft_strncmp(m->args[0], "cd", 3))
		return (1);
	else if (!ft_strncmp(m->args[0], "exit", 5))
		return (1);
	return (0);
}

int	builtins(t_m *m, int i, int n)
{
	if (!ft_strncmp(m->args[0], "echo", 5))
	{
		if (i > 0)
		{
			char	buf[BUFFER];
			int	ret = read(m->pipefd[2 * (i - 1)], buf, BUFFER);
			while (ret)
				write(1, buf, BUFFER);
			close(m->pipefd[2 * (i - 1)]);
		}
		if (n > 1 && i < n - 1)
		{
			if (dup2(m->pipefd[2 * i + 1], STDOUT_FILENO) == -1)
			{
				perror("dup2");
				free_ss(m->args);
				free_ss(m->coms);
				free(m->pipefd);
				exit(EXIT_FAILURE);
			}
			close(m->pipefd[2 * i + 1]);
		}
		return (echo(m, m->args));
	}
	else if (!ft_strncmp(m->args[0], "export", 7))
		return (expt(m, m->args));
	else if (!ft_strncmp(m->args[0], "pwd", 4))
	{
		if (getcwd(m->cwd, sizeof(m->cwd)))
		{
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
		return (cd(m, m->args[1]));
	else if (!ft_strncmp(m->args[0], "exit", 5))
	{
		free_ss(m->args);
		free_ss(m->coms);
		if (m->pipefd)
			free(m->pipefd);
		ft_lstclear(&m->infix, free);
		add_history(m->s);
		rl_free(m->s);
		exit(m->exit_code);
	}
	return (0);
}
