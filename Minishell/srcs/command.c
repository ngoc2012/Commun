/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/23 23:13:24 by ngoc             ###   ########.fr       */
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
	if (file)
		execve(file, m->args, m->env);
	else
		execve(m->args[0], m->args, m->env);
	if (file)
		free(file);
	exit_error(m, m->args[0], 127);
}
