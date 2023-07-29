/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/07/29 08:15:13 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	get_fd(t_m *m, int i, int n)
{
	int	fd;

	fd = 1;
	if (n < 2)
		return (fd);
	if (i)
	{
		if (i % 2)
		{
			//printf("bui main pipe0 closed\n");
			close(m->pipefd0[0]);
			close(m->pipefd0[1]);
		}
		else
		{
			//printf("bui main pipe1 closed\n");
			close(m->pipefd1[0]);
			close(m->pipefd1[1]);
		}
	}
	if (i < n - 1)
	{
		if (i % 2)
		{
			//printf("fd = pipefd1\n");
			fd = m->pipefd1[1];
		}
		else 
		{
			//printf("fd = pipefd0\n");
			fd = m->pipefd0[1];
		}
	}
	if (n > 3 && i && i < n - 2)
	{
		if (i % 2)
		{
			//printf("bui main pipe0 initiated\n");
			pipe(m->pipefd0);
		}
		else if (n > 2)
		{
			//printf("bui main pipe1 initiated\n");
			pipe(m->pipefd1);
		}
	}
	return (fd);
}

int	number_2_exit_code(const char *str)
{
	int	n;
	int	sign;

	n = 0;
	sign = 1;
	while (ft_strchr(" 	", *str))
		str++;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1;
	if (!str)
		return (-1);
	while (*str)
	{
		if (*str >= 48 && *str <= 57)
		{
			n *= 10;
			n += *str - 48;
			while (n > 256)
				n -= 256;
		}
		else
			return (-1);
		str++;
	}
	if (sign == -1)
		return (256 - n);
	else
		return (n);
}

int	is_max_long_long(const char *str)
{
	int	n;
	int	sign;
	int	i;

	n = 0;
	i = 0;
	sign = 1;
	while (ft_strchr(" 	", *str))
		str++;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str >= 48 && *str <= 57)
		{
			n *= 10;
			n += *str - 48;
			while (n >= 256)
			{
				n -= 256;
				i++;
			}
		}
		else
			return (0);
		str++;
	}
	if (sign == -1 && i == 92 && n > 0)
		return (1);
	if (sign == 1 && i == 92 && n > -1)
		return (1);
	return (0);
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
		return (echo0(m, m->args, fd));
	}
	else if (!ft_strncmp(m->args[0], "export", 7))
		return (expt(m, m->args));
	else if (!ft_strncmp(m->args[0], "unset", 6))
	{
		int	i;
		char	*s_e;

		i = 0;
		while (m->args[++i])
		{
			ft_lstremove_if(&m->envs, m->args[i], ft_strdcmp, free);
			s_e = 0;
			s_e = strjoinm(s_e, m->args[i], 0, ft_strlen(m->args[i]));
			s_e = strjoinm(s_e, "=", ft_strlen(s_e), 1);
			ft_lstadd_back(&m->envs, ft_lstnew(s_e));
		}
		m->exit_code = 0;
		return (1);
	}
	else if (!ft_strncmp(m->args[0], "pwd", 4))
	{
		fd = get_fd(m, i, n);
		ft_putstr_fd(m->cwd, fd);
		write(1, "\n", fd);
		m->exit_code = 0;
		return (1);
	}
	else if (!ft_strncmp(m->args[0], "cd", 3))
	{
		fd = get_fd(m, i, n);
		int	n_args;
		n_args = 0;
		while (m->args[n_args])
			n_args++;
		if (n_args > 2)
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
	else if (!ft_strncmp(m->args[0], "exit", 5))
	{
		if (n > 1)
			return (1);
		int	n_args;
		n_args = 0;
		while (m->args[n_args])
			n_args++;
		//printf("exit code0 : %d\n", m->exit_code);
		if (n_args == 2)
		{
			m->exit_code = number_2_exit_code(m->args[1]);
			if (m->exit_code == -1 || is_max_long_long(m->args[1]))
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(m->args[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2); 
				//printf("minishell: exit: %s: numeric argument required\n", m->args[1]);
				m->exit_code = 2;
			}
			//printf("exit code : %d\n", m->exit_code);
		}
		else if (n_args > 2)
			m->exit_code = 1;
		//printf("exit code : %d\n", m->exit_code);
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
		//if (WIFEXITED(m->exit_code))
		//	m->exit_code = WEXITSTATUS(m->exit_code);
		//else if (WIFSIGNALED(m->exit_code)) {
		//	int signal_number = WTERMSIG(m->exit_code);
		//	m->exit_code = 128 + signal_number;
		//}
		exit(m->exit_code);
	}
	return (0);
}
