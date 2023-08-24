/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/24 09:51:02 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pipe(t_m *m, int i, int n)
{
	if (i)
	{
		if (i % 2)
			close_pipe(m->pipefd0);
		else
			close_pipe(m->pipefd1);
	}
	if (n > 3 && i && i < n - 2)
	{
		if (i % 2)
			pipe(m->pipefd0);
		else if (n > 2)
			pipe(m->pipefd1);
	}
}

int	get_fd(t_m *m, int i, int n)
{
	int	fd;

	fd = 1;
	if (n < 2)
		return (fd);
	if (i < n - 1)
	{
		if (i % 2)
			fd = m->pipefd1[1];
		else
			fd = m->pipefd0[1];
	}
	return (fd);
}

int	export_env(t_m *m, int i, int n, int fd)
{
	char	**ss;

	if (!ft_strncmp(m->args[0], "export", 7))
	{
		set_pipe(m, i, n);
		if (m->argc == 1)
			return (expt_all(m, get_fd(m, i, n)));
		else if (n == 1)
			return (expt(m));
		return (1);
	}
	if (!ft_strncmp(m->args[0], "env", 4))
	{
		set_pipe(m, i, n);
		ss = m->env;
		while (*ss)
		{
			ft_putstr_fd(*ss++, get_fd(m, i, n));
			ft_putstr_fd("\n", get_fd(m, i, n));
		}
		m->exit_code = 0;
		return (1);
	}
	return (0);
}

int	pwd_cd(t_m *m, int i, int n, int fd)
{
	if (!ft_strncmp(m->args[0], "cd", 3))
	{
		set_pipe(m, i, n);
		if (m->argc > 2)
		{
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
			m->exit_code = 1;
			return (1);
		}
		else
		{
			cd(m, m->args[1]);
			return (1);
		}
	}
	else if (!ft_strncmp(m->args[0], "pwd", 4))
	{
		set_pipe(m, i, n);
		ft_putstr_fd(m->cwd, fd);
		write(1, "\n", fd);
		m->exit_code = 0;
		return (1);
	}
	return (0);
}

/*
Execute a built-in command elementary
*/
int	builtins(t_m *m, int i, int n)
{
	int	fd;
	int	j;

	fd = get_fd(m, i, n);
	if (!ft_strncmp(m->args[0], "echo", 5))
	{
		set_pipe(m, i, n);
		return (echo0(m, fd));
	}
	if (export_env(m, i, n, fd))
		return (1);
	if (pwd_cd(m, i, n, fd))
		return (1);
	if (!ft_strncmp(m->args[0], "unset", 6))
	{
		set_pipe(m, i, n);
		j = 0;
		while (m->args[++j])
			astr_remove(m->env, m->args[j], ft_strdcmp, free);
		m->exit_code = 0;
		return (1);
	}
	if (!ft_strncmp(m->args[0], "exit", 5))
		return (builtin_exit(m, i, n));
	return (0);
}
