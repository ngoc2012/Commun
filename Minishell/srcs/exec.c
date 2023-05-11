/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/11 17:53:26 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			exit(EXIT_SUCCESS);
		}
		perror("getcwd() error");
		exit(EXIT_FAILURE);
	}
	else if (!ft_strncmp(m->args[0], "cd", 3))
		cd(m, m->args[1]);
	if (ft_strchr(m->args[0], '/'))
		file = ft_strdup(m->args[0]);
	else
		file = check_file(m->args[0]);
	if (file)
		execve(file, m->args, m->env);
	free(file);
}

int	pipes(char *s, t_m *m)
{
	int		i;
	int		n;
	pid_t	pid;

	m->coms = ft_split(s, '|');
	n = -1;
	while (m->coms[++n])
		;
	i = -1;
	while (m->coms[++i])
	{
		m->args = split_args(m->coms[i], m);
		if (m->args[0])
		{
			if (!ft_strncmp(m->args[0], "exit", 5))
			{
				free_m(m);
				exit(EXIT_SUCCESS);
			}
			pid = fork();
			if (pid == -1)
			{
				perror("fork error");
				return ;
			} else if (pid == 0) {
				command(m);
				perror("execve error");
				return ;
			}
			else
				waitpid(pid, &m->exit_code, 0);
		}
		free_ss(m->args);
	}
	free_ss(m->coms);
}

