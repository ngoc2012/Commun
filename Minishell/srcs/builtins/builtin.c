/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/16 07:17:44 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

static int	export_env(t_m *m, int i)
{
	char	**ss;

	if (!ft_strncmp(m->args[0], "export", 7))
	{
		set_pipe(m, i);
		return (expt_all(m, get_fd(m, i)));
	}
	if (!ft_strncmp(m->args[0], "env", 4))
	{
		set_pipe(m, i);
		ss = m->env;
		while (*ss)
		{
			if (ft_strchr(*ss, '='))
			{
				ft_putstr_fd(*ss, get_fd(m, i));
				ft_putstr_fd("\n", get_fd(m, i));
			}
			ss++;
		}
		m->exit_code = 0;
		return (1);
	}
	return (0);
}

static int	pwd_cd(t_m *m, int i, int fd)
{
	if (!ft_strncmp(m->args[0], "cd", 3))
	{
		set_pipe(m, i);
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
		set_pipe(m, i);
		ft_putstr_fd(m->cwd, fd);
		write(fd, "\n", 1);
		m->exit_code = 0;
		return (1);
	}
	return (0);
}

static int	unset_exit(t_m *m, int i, int fd)
{
	int	j;

	(void)fd;
	if (!ft_strncmp(m->args[0], "unset", 6))
	{
		set_pipe(m, i);
		j = 0;
		while (m->args[++j])
			astr_remove(m->env, m->args[j], ft_strdcmp, free);
		m->exit_code = 0;
		return (1);
	}
	if (!ft_strncmp(m->args[0], "exit", 5))
	{
		set_pipe(m, i);
		return (builtin_exit(m));
	}
	return (0);
}

/*
Execute a built-in command elementary
*/
int	builtins(t_m *m, int i)
{
	int	fd;

	fd = get_fd(m, i);
	if (!ft_strncmp(m->args[0], "echo", 5))
	{
		set_pipe(m, i);
		return (echo0(m, fd));
	}
	if (export_env(m, i))
		return (1);
	if (pwd_cd(m, i, fd))
		return (1);
	return (unset_exit(m, i, fd));
}
