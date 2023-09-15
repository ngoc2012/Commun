/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:01:37 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/15 21:39:58 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*relative_path1(t_m *m, char *path)
{
	char	*p;

	if (*path == '~')
	{
		p = strjoinm(0, get_home(m), 0, ft_strlen(get_home(m)));
		p = strjoinm(p, &path[1], ft_strlen(p), ft_strlen(&path[1]));
		return (p);
	}
	if (!ft_strncmp(path, ".", 2))
	{
		p = strjoinm(0, m->cwd, 0, ft_strlen(m->cwd));
		p = strjoinm(p, "/.", ft_strlen(p), 2);
		return (p);
	}
	if (!ft_strncmp(path, "./", 3))
	{
		p = strjoinm(0, m->cwd, 0, ft_strlen(m->cwd));
		if (m->cwd[ft_strlen(m->cwd) - 1] == '/')
			p = strjoinm(p, "./", ft_strlen(p), 2);
		else
			p = strjoinm(p, "/./", ft_strlen(p), 3);
		return (p);
	}
	return (0);
}

static char	*relative_path2(t_m *m, char *path, int i)
{
	char	*p;

	if (!ft_strncmp(path, "..", 3))
	{
		getcwd(m->cwd, sizeof(m->cwd));
		if (!ft_strncmp(m->cwd, "/", 2) || !ft_strncmp(m->cwd, "//", 3))
			return (ft_strdup("/"));
		p = strjoinm(0, m->cwd, 0, ft_strlen(m->cwd));
		i = ft_strlen(p);
		if (i > 0)
		{
			if (i > 1 && p[i - 1] == '/')
				i--;
			while (i > 2 && !ft_strncmp(&p[i - 2], "/.", 2))
				i -= 2;
			while (p[--i] != '/' && p[i])
				;
		}
		p[i] = 0;
		return (p);
	}
	return (0);
}

static char	*relative_path3(t_m *m, char *path, int i)
{
	char	*p;
	int		j;

	j = 1;
	if (!ft_strncmp(path, "../", 3))
	{
		getcwd(m->cwd, sizeof(m->cwd));
		p = strjoinm(0, m->cwd, 0, ft_strlen(m->cwd));
		i = ft_strlen(p);
		while (p[--i] != '/' && p[i])
			;
		while (!ft_strncmp(&path[j * 3], "../", 3))
		{
			j++;
			if (i > 0)
				while (p[--i] != '/' && p[i])
					;
		}
		p[i] = 0;
		p = strjoinm(p, "/", ft_strlen(p), 1);
		return (strjoinm(p, &path[j * 3],
				ft_strlen(p), ft_strlen(&path[j * 3])));
	}
	return (0);
}

static char	*relative_path4(t_m *m, char *path)
{
	char	*p;

	if (!ft_strncmp(path, "//", 3))
		return (ft_strdup("//"));
	if (!ft_strncmp(path, "./", 2))
	{
		p = strjoinm(0, m->cwd, 0, ft_strlen(m->cwd));
		return (strjoinm(p, &path[1], ft_strlen(p), ft_strlen(&path[1])));
	}
	if (*path != '/')
	{
		getcwd(m->cwd, sizeof(m->cwd));
		p = strjoinm(0, m->cwd, 0, ft_strlen(m->cwd));
		p = strjoinm(p, "/", ft_strlen(p), 1);
		return (strjoinm(p, &path[0], ft_strlen(p), ft_strlen(&path[0])));
	}
	return (0);
}

char	*abs_path(t_m *m, char *path)
{
	char	*p;
	int		i;

	i = 0;
	p = relative_path0(m, path);
	if (p || (!path && !get_home(m)))
		return (p);
	if (!ft_strncmp(path, ".", 2))
	{
		getcwd(m->cwd, sizeof(m->cwd));
		return (strjoinm(0, m->cwd, 0, ft_strlen(m->cwd)));
	}
	p = relative_path1(m, path);
	if (p)
		return (p);
	p = relative_path2(m, path, i);
	if (p)
		return (p);
	p = relative_path3(m, path, i);
	if (p)
		return (p);
	p = relative_path4(m, path);
	if (p)
		return (p);
	return (strjoinm(0, path, 0, ft_strlen(path)));
}
