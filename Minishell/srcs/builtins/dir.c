/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:01:37 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/03 12:57:55 by ngoc             ###   ########.fr       */
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
	char	d;
	char	*s;
	char	*p;

	d = ' ';
	m_free = 0;
	if (!path)
	{
		p = get_home(m);
		m_free = 1;
	}
	else if (*path == '"' || *path == '\'')
	{
		d = path[0];
		path++;
		i = -1;
		while (path[++i] && path[i] != d)
			;
		if (path[i] == d)
		{
			path[i] = 0;
			p = path;
		}
		else
		{
			p = 0;
			p = strjoinm(p, path, 0, ft_strlen(path));
			int	end;
			end = 0;
			while (!end)
			{
				p = strjoinm(p, "\\n", ft_strlen(p), 2);
				s = readline("> ");
				i = -1;
				while (s[++i] && s[i] != d)
					;
				if (s[i] == d)
				{
					end = 1;
					p = strjoinm(p, s, ft_strlen(p), i);
				}
				else
					p = strjoinm(p, s, ft_strlen(p), ft_strlen(s));
			}
			path = p;
			m_free = 1;
		}
	}
	else if (*path == '~')
	{
		p = get_home(m);
		p = strjoinm(p, &path[1], ft_strlen(p), ft_strlen(&path[1]));
		m_free = 1;
	}
	else if (*path == '.' && *(path + 1) == '/')
	{
		pwd(m);
		p = 0;
		p = strjoinm(p, m->cwd, 0, ft_strlen(m->cwd));
		p = strjoinm(p, &path[1], ft_strlen(p), ft_strlen(&path[1]));
		//printf("|%s|\n", p);
		m_free = 1;
	}
	else if (*path == '.' && *(path + 1) == '.' && *(path + 2) == '/')
	{
		pwd(m);
		i = ft_strlen(m->cwd);
		int	j = 1;
		while (m->cwd[--i] != '/' && m->cwd[i])
			;
		while (path[j * 3] == '.' && path[j * 3 + 1] == '.' && path[j * 3 + 2] == '/')
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
		m_free = 1;
	}
	else if (*path != '/')
	{
		pwd(m);
		p = 0;
		p = strjoinm(p, m->cwd, 0, ft_strlen(m->cwd));
		p = strjoinm(p, "/", ft_strlen(p), 1);
		p = strjoinm(p, &path[0], ft_strlen(p), ft_strlen(&path[0]));
		//printf("|%s|\n", p);
		m_free = 1;
	}
	else
		p = path;
	char	*p0 = str_env(p, ft_strlen(p), m, d);
	if (chdir(p0))
	{
		//printf("|%s|\n", p0);
		s = 0;
		s = strjoinm(s, "minishell: cd: ", 0, 15);
		if (d != ' ')
			s = strjoinm(s, &d, ft_strlen(s), 1);
		char	*path0 = str_env(path, ft_strlen(path), m, d);
		s = strjoinm(s, path0, ft_strlen(s), ft_strlen(path0));
		if (d != ' ')
			s = strjoinm(s, &d, ft_strlen(s), 1);
		perror(s);
		free(path0);
		if (s)
			free(s);
		m->exit_code = 1;
	}
	else
		m->exit_code = 0;
	free(p0);
	if (m_free)
		free(p);
}
