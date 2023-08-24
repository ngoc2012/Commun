/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/17 16:07:27 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_process_level;

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
		s = strjoinm(0, *ss, 0, ft_strlen(*ss));
		s = strjoinm(s, "/", ft_strlen(s), 1);
		s = strjoinm(s, file, ft_strlen(s), ft_strlen(file));
		if (access(s, F_OK) != -1)
		{
			free_array_str(&ss0, 1);
			return (s);
		}
		ss++;
		free(s);
	}
	free_array_str(&ss0, 0);
	return (0);
}

int	command(t_m *m, int n)
{
	char	*file;

	file = check_file(m->args[0]);
	//printf("fork %s\n", m->args[0]);
	if (file)
		execve(file, m->args, m->env);
	else
		execve(m->args[0], m->args, m->env);
	perror(m->args[0]);
	if (file)
		free(file);
	free_m(m);
	ft_lstclear(&m->infix, free);
	exit(127);
}

void	process(t_m *m, int i, int n)
{
	int		j;

	//printf("fork\n");
	m->pid[i] = fork();
	if (m->pid[i] == -1)
	{
		perror("fork error");
		free_m(m);
		return ;
	}
	else if (!m->pid[i])
	{
		//printf("Process %d (%d/%d) start\n", getpid(), i, n);
		if (n > 1)
		{
			//printf("Process %d (%d/%d) start\n", getpid(), i, n);
			//printf("Process %d pipefd[0] = %d, pipefd[1] = %d\n", getpid(), m->pipefd0[0], m->pipefd0[1]);
			// First process
			if (!i)
			{
				if (n > 2)
				{
					//printf("Process %d (%d/%d) closed pipe1\n", getpid(), i, n);
					close(m->pipefd1[0]);
					close(m->pipefd1[1]);
				}
				close(m->pipefd0[0]);
				if (dup2(m->pipefd0[1], STDOUT_FILENO) == -1)
				{
					perror("dup2 i=0");
					free_array_str(&m->args, 0);
					free_array_str(&m->coms, 0);
					exit(EXIT_FAILURE);
				}
				close(m->pipefd0[1]);
			}
			// Last process
			else if (n == 2)
			{
				close(m->pipefd0[1]);
				if (dup2(m->pipefd0[0], STDIN_FILENO) == -1)
				{
					perror("dup2 last 1");
					free_array_str(&m->args, 0);
					free_array_str(&m->coms, 0);
					exit(EXIT_FAILURE);
				}
				close(m->pipefd0[0]);
			}
			else if (i == n - 1)
			{
				if (i % 2)
				{
					close(m->pipefd1[0]);
					close(m->pipefd1[1]);
					//printf("Process %d (%d/%d) dup2 pipe0 STDIN\n", getpid(), i, n);
					close(m->pipefd0[1]);
					if (dup2(m->pipefd0[0], STDIN_FILENO) == -1)
					{
						perror("dup2 last 2");
						free_array_str(&m->args, 0);
						free_array_str(&m->coms, 0);
						exit(EXIT_FAILURE);
					}
					close(m->pipefd0[0]);
				}
				else
				{
					close(m->pipefd0[0]);
					close(m->pipefd0[1]);
					//printf("Process %d (%d/%d) dup2 pipe1 STDIN\n", getpid(), i, n);
					close(m->pipefd1[1]);
					if (dup2(m->pipefd1[0], STDIN_FILENO) == -1)
					{
						perror("dup2 last 3");
						free_array_str(&m->args, 0);
						free_array_str(&m->coms, 0);
						exit(EXIT_FAILURE);
					}
					close(m->pipefd1[0]);
				}
			}
			// Intermediate process
			else if (i % 2)
			{
				//printf("Process %d (%d/%d) dup2 pipe0 STDIN\n", getpid(), i, n);
				close(m->pipefd0[1]);
				if (dup2(m->pipefd0[0], STDIN_FILENO) == -1)
				{
					perror("dup2 inter 1");
					free_array_str(&m->args, 0);
					free_array_str(&m->coms, 0);
					exit(EXIT_FAILURE);
				}
				close(m->pipefd0[0]);
				//printf("Process %d (%d/%d) dup2 pipe1 STDOUT\n", getpid(), i, n);
				close(m->pipefd1[0]);
				if (dup2(m->pipefd1[1], STDOUT_FILENO) == -1)
				{
					perror("dup2 inter 2");
					free_array_str(&m->args, 0);
					free_array_str(&m->coms, 0);
					exit(EXIT_FAILURE);
				}
				close(m->pipefd1[1]);
			}
			else
			{
				//printf("Process %d (%d/%d) dup2 pipe1 STDIN\n", getpid(), i, n);
				close(m->pipefd1[1]);
				if (dup2(m->pipefd1[0], STDIN_FILENO) == -1)
				{
					perror("dup2 inter 3");
					free_array_str(&m->args, 0);
					free_array_str(&m->coms, 0);
					exit(EXIT_FAILURE);
				}
				close(m->pipefd1[0]);
				//printf("Process %d (%d/%d) dup2 pipe0 STDOUT\n", getpid(), i, n);
				close(m->pipefd0[0]);
				if (dup2(m->pipefd0[1], STDOUT_FILENO) == -1)
				{
					perror("dup2 inter 4");
					free_array_str(&m->args, 0);
					free_array_str(&m->coms, 0);
					exit(EXIT_FAILURE);
				}
				close(m->pipefd0[1]);
			}
		}
		command(m, n);
	}
	else
	{
		if (i)
		{
			if (i % 2)
			{
				close(m->pipefd0[0]);
				close(m->pipefd0[1]);
			}
			else if (n > 2)
			{
				close(m->pipefd1[0]);
				close(m->pipefd1[1]);
			}
		}
		//printf("Wait for %d\n", m->pid[i]);
		waitpid(m->pid[i], &m->exit_code, 0);
		//printf("Process %d finished\n", m->pid[i]);
		if (m->has_child)
		{
			g_process_level = 0;
			m->has_child = 0;
			//printf("Process %d finished - %d\n", getpid(), g_process_level);
		}
		if (WIFEXITED(m->exit_code))
			m->exit_code = WEXITSTATUS(m->exit_code);
		else if (WIFSIGNALED(m->exit_code)) {
			int signal_number = WTERMSIG(m->exit_code);
			m->exit_code = 128 + signal_number;
		}
		if (n > 3 && i && i < n - 2)
		{
			if (i % 2)
				pipe(m->pipefd0);
			else if (n > 2)
				pipe(m->pipefd1);
		}
	}
}
