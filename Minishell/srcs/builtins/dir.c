/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:01:37 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/04 21:34:07 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_m *m)
{
	if (getcwd(m->cwd, sizeof(m->cwd)))
		m->exit_code = 0;
	else
	{
		perror("getcwd() error");
		m->exit_code = 1;
	}
}

char	*get_home(t_m *m)
{
	char	*p;
	char	*u;

	u = get_env_name("USER", m->env);
	p = 0;
	p = strjoinm(p, "/home/", 0, 6);
	if (!u || !p)
		return (0);
	p = strjoinm(p, u, ft_strlen(p), ft_strlen(u));
	return (p);
}

void	cd(t_m *m, char *path)
{
	int		i;
	int		m_free;
	char	*s;
	char	*p;

	m_free = 1;
	if (!path)
	{
		p = get_home(m);
		free(p);
		return ;
	}
	path = parse(path, m);
	//printf("|%s|\n", path);
	if (*path == '~')
	{
		p = get_home(m);
		p = strjoinm(p, &path[1], ft_strlen(p), ft_strlen(&path[1]));
	}
	//else if (*path == '.' && *(path + 1) == '/')
	else if (!ft_strncmp(path, "./", 2))
	{
		pwd(m);
		p = 0;
		p = strjoinm(p, m->cwd, 0, ft_strlen(m->cwd));
		p = strjoinm(p, &path[1], ft_strlen(p), ft_strlen(&path[1]));
		//printf("|%s|\n", p);
	}
	//else if (*path == '.' && *(path + 1) == '.' && !(*(path + 2)))
	else if (!ft_strncmp(path, "..", 3))
	{
		pwd(m);
		i = ft_strlen(m->cwd);
		if (i > 0)
			while (m->cwd[--i] != '/' && m->cwd[i])
				;
		p = 0;
		p = strjoinm(p, m->cwd, 0, i);
	}
	//else if (*path == '.' && *(path + 1) == '.' && *(path + 2) == '/')
	else if (!ft_strncmp(path, "../", 3))
	{
		pwd(m);
		i = ft_strlen(m->cwd);
		int	j = 1;
		while (m->cwd[--i] != '/' && m->cwd[i])
			;
		//while (path[j * 3] == '.' && path[j * 3 + 1] == '.' && path[j * 3 + 2] == '/')
		while (!ft_strncmp(&path[j * 3], "../", 3))
		{
			j++;
			//printf("|j = %d|\n", j);
			if (i > 0)
				while (m->cwd[--i] != '/' && m->cwd[i])
					;
		}
		//printf("|%d|\n", i);
		p = 0;
		p = strjoinm(p, m->cwd, 0, i);
		p = strjoinm(p, "/", ft_strlen(p), 1);
		p = strjoinm(p, &path[j * 3], ft_strlen(p), ft_strlen(&path[j * 3]));
		//printf("|%s|\n", p);
	}
	else if (*path != '/')
	{
		pwd(m);
		p = 0;
		p = strjoinm(p, m->cwd, 0, ft_strlen(m->cwd));
		p = strjoinm(p, "/", ft_strlen(p), 1);
		p = strjoinm(p, &path[0], ft_strlen(p), ft_strlen(&path[0]));
		//printf("|%s|\n", p);
	}
	else
	{
		p = path;
		m_free = 0;
	}
	if (chdir(p))
	{
		s = 0;
		s = strjoinm(s, "minishell: cd: ", 0, 15);
		s = strjoinm(s, path, ft_strlen(s), ft_strlen(path));
		perror(s);
		free(s);
		m->exit_code = 1;
	}
	else
		m->exit_code = 0;
	free(p);
	if (m_free)
		free(path);
}
