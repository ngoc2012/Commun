/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/10 16:16:23 by minh-ngu         ###   ########.fr       */
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

void	exec(t_m *m, char *command, char **args)
{
	char	*s;
	pid_t	pid;

	if (ft_strchr(args[0], '/'))
		s = ft_strdup(args[0]);
	else
		s = check_file(args[0]);
	if (!s)
		return ;
	//printf("exec.c: %s\n", s);
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		return ;
	} else if (pid == 0) {
		execve(s, args, m->env);
		perror("execve error");
		return ;
	}
	else
		waitpid(pid, &m->exit_code, 0);
	free(s);
}
