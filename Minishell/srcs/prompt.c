/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 21:34:57 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/20 11:44:48 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*short_link(char *cwd, t_m *m)
{
	char	*home;

	home = get_env("HOME", m->env);
	if (!home)
		return (0);
	if (!ft_strncmp(cwd, home, ft_strlen(home)))
		return (&cwd[ft_strlen(home)]);
	return (0);
}

void	get_prompt(t_m *m, char *prompt)
{
	char	*s;

	ft_strlcpy(prompt, "minishell:", PATH_MAX);
	s = short_link(m->cwd, m);
	if (s)
	{
		ft_strlcat(prompt, "~", PATH_MAX);
		ft_strlcat(prompt, s, PATH_MAX);
	}
	else
		ft_strlcat(prompt, m->cwd, PATH_MAX);
	ft_strlcat(prompt, "$ ", PATH_MAX);
}

void	append_hc(t_m *m)
{
	int		fd;
	char	*path;

	path = abs_path(m, HISTORY);
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0664);
	free(path);
	if (fd == -1)
		return ;
	write(fd, m->s, ft_strlen(m->s));
	write(fd, "\n", 1);
	close(fd);
}

void	get_hc(t_m *m)
{
	int		fd;
	char	*path;
	char	*s;

	path = abs_path(m, HISTORY);
	fd = open(path, O_RDONLY);
	free(path);
	if (fd == -1)
		return ;
	s = get_next_line(fd);
	while (s)
	{
		if (ft_strlen(s) > 1)
		{
			s[ft_strlen(s) - 2] = 0;
			add_history(s);
		}
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
}
