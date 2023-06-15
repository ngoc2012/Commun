/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/06/14 17:23:27 by ngoc             ###   ########.fr       */
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

	file = check_file(m->args[0]);
	if (!file)
		file = ft_strdup(m->args[0]);
	execve(file, m->args, m->env);
	perror(file);
	free(file);
	free_ss(m->args);
	free_ss(m->coms);
	rl_free(m->s);
	//if (m->pipefd)
	//	free(m->pipefd);
	ft_lstclear(&m->infix, free);
	exit(127);
}

void	process(t_m *m, int i, int n)
{
	int		j;
	pid_t	pid;

	//printf("fork\n");
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		free_ss(m->args);
		free_ss(m->coms);
		//free(m->pipefd);
		return ;
	}
	else if (!pid)
	{
		if (n > 1)
		{
			if (i < n - 1)
			{
				if (!i)
					close(m->pipefd[0]);
				if (dup2(m->pipefd[1], STDOUT_FILENO) == -1)
				{
					perror("dup2");
					free_ss(m->args);
					free_ss(m->coms);
					exit(EXIT_FAILURE);
				}
				close(m->pipefd[1]);
			}
			if (i > 0)
			{
				if (i == n - 1)
					close(m->pipefd[1]);
				if (dup2(m->pipefd[0], STDIN_FILENO) == -1)
				{
					perror("dup2");
					free_ss(m->args);
					free_ss(m->coms);
					exit(EXIT_FAILURE);
				}
				close(m->pipefd[0]);
			}
		}
		command(m);
	}
	else
	{
		//if (i > 0)
		//{
		//	close(m->pipefd[2 * (i - 1)]);
		//	close(m->pipefd[2 * (i - 1) + 1]);
		//}
		close(m->pipefd[0]);
		close(m->pipefd[1]);
		waitpid(pid, &m->exit_code, 0);
	}
}

