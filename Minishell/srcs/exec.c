/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/14 17:44:31 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"

static char	*check_file(char *file)
{
	char	*path;
	char	**ss;
	char	**ss0;
	char	*s;

	path = getenv("PATH");
	if (!path)
		return (0);
	ss = ft_split(path, ':');
	ss0 = ss;
	while (*ss)
	{
		s = 0;
		s = strjoinm(s, *ss, 0, ft_strlen(*ss));
		s = strjoinm(s, "/", ft_strlen(s), 1);
		s = strjoinm(s, file, ft_strlen(s), ft_strlen(file));
		if (access(s, F_OK) != -1)
		{
			free_ss(ss0);
			return (s);
		}
		ss++;
		free(s);
	}
	free_ss(ss0);
	return (0);
}

int	command(t_m *m)
{
	char	*file;

	if (!ft_strncmp(m->args[0], "echo", 5))
		echo(m, m->args);
	else if (!ft_strncmp(m->args[0], "pwd", 4))
	{
		if (getcwd(m->cwd, sizeof(m->cwd)))
		{
			ft_putstr_fd(m->cwd, 1);
			write(1, "\n", 1);
			free_m(m);
			exit(EXIT_SUCCESS);
		}
		free_m(m);
		perror("getcwd() error");
		exit(EXIT_FAILURE);
	}
	else if (!ft_strncmp(m->args[0], "cd", 3))
		cd(m, m->args[1]);
	file = check_file(m->args[0]);
	if (!file)
		file = ft_strdup(m->args[0]);
	execve(file, m->args, m->env);
	perror(file);
	free(file);
	free_m(m);
	exit(127);
}

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
		m->args = split_args(m->coms[i], m);
		printf("exec.c 1:%s\n", s);
		if (m->args[0])
		{
			if (!ft_strncmp(m->args[0], "exit", 5))
			{
				free_m(m);
				exit(EXIT_SUCCESS);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
			free_ss(m->args);
			free_ss(m->coms);
			free(m->pipefd);
			return (0);
		}
		else if (!pid)
		{
			if (n > 1)
			{
				j = -1;
				while (++j < 2 * (n - 1))
					if (!(i < n - 1 && j == 2 * i + 1) && !(i > 0 && j == 2 * (i - 1)))
						close(m->pipefd[j]);
				if (i < n - 1)
				{
					if (dup2(m->pipefd[2 * i + 1], STDOUT_FILENO) == -1)
					{
						perror("dup2");
						free_m(m);
						exit(EXIT_FAILURE);
					}
					close(m->pipefd[2 * i + 1]);
				}
				if (i > 0)
				{
					if (dup2(m->pipefd[2 * (i - 1)], STDIN_FILENO) == -1)
					{
						perror("dup2");
						free_m(m);
						exit(EXIT_FAILURE);
					}
					close(m->pipefd[2 * (i - 1)]);
				}
			}
			command(m);
		}
		else
		{
			if (i > 0)
			{
				close(m->pipefd[2 * (i - 1)]);
				close(m->pipefd[2 * (i - 1) + 1]);
			}
			waitpid(pid, &m->exit_code, 0);
		}
		free_ss(m->args);
	}
	if (m->pipefd)
		free(m->pipefd);
	free_ss(m->coms);
	return (1);
}

