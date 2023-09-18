/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 21:34:57 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/18 10:59:52 by ngoc             ###   ########.fr       */
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

	ft_strlcpy(prompt, COLOR_BOLD_GREEN, PATH_MAX);
	ft_strlcat(prompt, "minishell:", PATH_MAX);
	ft_strlcat(prompt, COLOR_BOLD_CYAN, PATH_MAX);
	s = short_link(m->cwd, m);
	if (s)
	{
		ft_strlcat(prompt, "~", PATH_MAX);
		ft_strlcat(prompt, s, PATH_MAX);
	}
	else
		ft_strlcat(prompt, m->cwd, PATH_MAX);
	ft_strlcat(prompt, COLOR_OFF, PATH_MAX);
	ft_strlcat(prompt, "$ ", PATH_MAX);
}

void	append_hc(t_m *m)
{
	add_history(m->s);
	path = abs_path(m, HISTORY);
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0664);
	free(path);
	if (fd == -1)
		return ;
	s = get_next_line(fd);
	while (s)
	{
		write(fd, s, ft_strlen(s));
		free(s);
		write(fd, "\n", 1);
		s = get_next_line(fd);
	}
	close(fd);
}

void	get_hc(t_m *m)
{
	path = abs_path(m, HISTORY);
	free(path);
	if (fd == -1)
	{
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		close(fd)
		return ;
	}
	s = get_next_line(fd);
	while (s)
	{
		add_history(s);
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
}
