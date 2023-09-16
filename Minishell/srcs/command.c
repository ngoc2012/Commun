/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/16 03:42:27 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_file(char *file, t_m *m)
{
	char	*path;
	char	**ss;
	char	**ss0;
	char	*s;

	path = get_env("PATH", m->env);
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

void	convert_exit_code(t_m *m)
{
	if (WIFEXITED(m->exit_code))
		m->exit_code = WEXITSTATUS(m->exit_code);
	else if (WIFSIGNALED(m->exit_code))
		m->exit_code = WTERMSIG(m->exit_code) + 128;
}

static int	check_dir(char *s)
{
	DIR	*d;

	if (!s || !*s)
		return (0);
	d = opendir(s);
	if (d)
	{
		closedir(d);
		return (1);
	}
	return (0);
}

void	command(t_m *m)
{
	char				*file;

	signal(SIGQUIT, SIG_DFL);
	file = check_file(m->args[0], m);
	if (file)
	{
		//printf("file\n");
		execve(file, m->args, m->env);
	}
	else if (ft_strncmp(m->args[0], "minishell", 10))
	{
		//printf("command\n");
		// export OLDSHLVL=1
		// Copy env;
		execve(m->args[0], m->args, m->env);
		//  OLDSHLVL=1
		// delete env;
	}
	if (file)
		free(file);
	ft_putstr_fd(m->args[0], 2);
	if (check_dir(m->args[0]))
	{
		m->exit_code = 126;
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else
	{
		ft_putstr_fd(": command not found\n", 2);
		m->exit_code = 127;
	}
	free_heredoc(m);
	free_m(m, 1);
	exit(m->exit_code);
}
